#include "scene.hpp"
#include <QList>
#include <vector>
#include <limits>
#include <future>
#include <thread>
#include <chrono>

Scene::Scene(){

}

Scene::Scene(Camera * camera, 
             QVector<Light*> lights, 
             QVector<ShadedObject*> objects, 
             int threads)
{
    _camera = camera;
    _lights = lights;
    _objects = objects;
    _threads  = threads;
    focalPoint = camera->normal() * (-1 * camera->focus());
}

Scene::~Scene(){
}

point3D Scene::getPixel(const int &i, 
                        const int &j)
{
    point3D imgPlaneIntersect(_camera->resolution().first * (i-(_camera->size().first/2)),_camera->resolution().second * (j-(_camera->size().second/2)),0);
    point3D rayDirection = imgPlaneIntersect - focalPoint;
    rayDirection = rayDirection.norm();
    double minDistance = std::numeric_limits<double>::max();
    int interest = -1;
    point3D shadowRay, intersection, normal, intersection2, normal2;
    bool objecthit = false;

    //this loop detects of the ray intersects an object 
    //and when multiple objects,
    //finds the closest.
    
    for(int k = 0; k < _objects.size(); k++){
        if(_objects[k]->intersects(focalPoint, rayDirection, intersection, normal)){

            double distance = sqrt((intersection - focalPoint).dot(intersection - focalPoint));
            if(distance < minDistance){
                minDistance = distance;
                interest = k;
                intersection2 = intersection;
                normal2 = normal;
                objecthit = true;
            }
        }
    }
    point3D pixColor(0,0,0);
    if(objecthit) {
        //loop through all the lights
        for(int k = 0; k < _lights.size() /*&& k < 1*/; k++){
            //determine if there is another object blocking the light
            bool shaded = false;
            shadowRay = (_lights[k]->location() - intersection2).norm();
            if(shadowRay.dot(normal2) > 0){
                point3D trash1;
                point3D trash2;
                for(int l = 0; l < _objects.size() && shaded == false; l++){
                    //test for intersection with other objects
                    if(_objects[l]->intersects(intersection2, shadowRay, trash1, trash2)){
                        if(trash1.z() > 0){
                            shaded = true;
                        }
                    }
                }
                if(!shaded){
                    double scale = normal2.dot(shadowRay.norm());
                    if (scale < 0){
                        scale *= -1;
                    }
                    point3D colors(_objects[interest]->color().red(), _objects[interest]->color().green(), _objects[interest]->color().blue());
                    pixColor = pixColor + colors*_lights[k]->intensity()*scale;
                }//end color calculation
            }//end loop through lights
        }
    }//end object shading effects
    
    return pixColor;
}

void getRange(int bottom, int top, 
              int row_length,
              Scene *scene,
              int num,
              std::vector<point3D> & pixMatrix){

    qDebug() << num << ": bottom: " << bottom;
    qDebug() << num << ":    top: " << top;
    for ( int i = bottom; i < top; i++){
        pixMatrix[i] = scene->getPixel(i/row_length, i%row_length);
    }
}

QImage Scene::renderScene(){
    QImage image(_camera->size().first, _camera->size().second, 
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::black);
    std::vector<point3D> pixMatrix;
    pixMatrix.assign(_camera->size().first*_camera->size().second, point3D(0,0,0));
    double maxRed = 0;
    double maxGreen = 0;
    double maxBlue = 0;
    //threading
    std::chrono::time_point<std::chrono::system_clock>start, end;
    std::chrono::duration<double> elapsed_seconds;
    qDebug() << _threads;
    

    start = std::chrono::system_clock::now();

    std::vector<std::thread> threadObjs;
    int bottom = 0;
    int top = pixMatrix.size()/_threads;
    for (int c = 0; c + 1 < _threads; c++) {
        threadObjs.push_back(std::thread(getRange, bottom, top
                                         , _camera->size().first
                                         , this
                                         , c
                                         , std::ref(pixMatrix)));
        bottom = top+1;
        top = top+pixMatrix.size()/_threads;
    }
    threadObjs.push_back(std::thread(getRange, bottom, pixMatrix.size()
                                     , _camera->size().first
                                     , this
                                     , int(200)
                                     , std::ref(pixMatrix)));
    for (int c = 0; c < _threads; c++) {
        threadObjs[c].join();
    }

    for( int c = 0; c < pixMatrix.size(); c++) {
        if(maxRed < pixMatrix[c].x()){
            maxRed = pixMatrix[c].x();
        }
        if(maxGreen < pixMatrix[c].y()){
            maxGreen = pixMatrix[c].y();
        }
        if(maxBlue < pixMatrix[c].z()){
            maxBlue = pixMatrix[c].z();
        }
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    qDebug() << "Determine pixel color: Elapsed time: " 
             << elapsed_seconds.count() << "s";
 
    start = std::chrono::system_clock::now();
 
   //loop through the pixMatrix to create the image
    for(int k = 0; k < pixMatrix.size(); k++){
        QColor newColor;
        if(maxRed > 255 || maxBlue > 255 || maxGreen > 255){
            newColor.setRgb(pixMatrix[k].x()*(255/maxRed), pixMatrix[k].y()*(255/maxGreen), pixMatrix[k].z()*(255/maxBlue));
        }
        else{
            newColor.setRgb(pixMatrix[k].x(), pixMatrix[k].y(), pixMatrix[k].z());
        }
        image.setPixel((k/_camera->size().first),(k%_camera->size().first),newColor.rgb());
    }
    
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    qDebug() << "Set pixel color:       Elapsed time: " 
             << elapsed_seconds.count() << "s";
    return image;
}

