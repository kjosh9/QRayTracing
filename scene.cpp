#include "scene.hpp"
#include <QList>
#include <vector>
#include <limits>
#include <thread>
#include <mutex>
#include <chrono>

Scene::Scene(){

}

Scene::Scene(Camera * camera, 
             QVector<Light*> lights, 
             QVector<ShadedObject*> objects, 
             int /*threads*/)
{
    _camera = camera;
    _lights = lights;
    _objects = objects;
    focalPoint = camera->normal() * (-1 * camera->focus());
    _threads = std::thread::hardware_concurrency();
    if (_threads == 0) {
        _threads = 1;
    } else if (_threads > 2) {
        _threads = _threads/ 2;
    }
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

void getRange(int start_pix,
              int finish_pix,
              int row_length,
              Scene *scene,
              int num,
              std::vector<point3D> & pixMatrix){
    std::mutex m;
    qDebug() << num << ": start: " << start_pix;
    qDebug() << num << ":finish: " << finish_pix;
    for ( int i = start_pix; i < finish_pix; i++){
        auto value = scene->getPixel(i/row_length, i%row_length);
        std::lock_guard<std::mutex> lk(m);
        pixMatrix[i] = value;
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
    std::vector<std::thread> threads;
    int start_pix = 0;
    int finish_pix = pixMatrix.size()/_threads;
    int range = finish_pix;
    qDebug() << "Total pix: " << pixMatrix.size();
    qDebug() << "Range: " << range;
    for (int i = 0; i < _threads; i++) {
        threads.push_back(std::thread(getRange,
                                      start_pix,
                                      finish_pix,
                                      _camera->size().first,
                                      this,
                                      i,
                                      std::ref(pixMatrix)));
        start_pix = finish_pix+1;
        finish_pix = range+finish_pix;
    }
    for (auto & thread: threads) {
        thread.join();
    }

    for(point3D & pixel: pixMatrix) {
        if(maxRed < pixel.x()){
            maxRed = pixel.x();
        }
        if(maxGreen < pixel.y()){
            maxGreen = pixel.y();
        }
        if(maxBlue < pixel.z()){
            maxBlue = pixel.z();
        }
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    qDebug() << "Determine pixel color: Elapsed time: " 
             << elapsed_seconds.count() << "s";
 
    start = std::chrono::system_clock::now();
 
   //loop through the pixMatrix to create the image
    int i{0};
    for(point3D & pixel: pixMatrix){
        QColor newColor;
        if(maxRed > 255 || maxBlue > 255 || maxGreen > 255){
            newColor.setRgb(pixel.x()*(255/maxRed), pixel.y()*(255/maxGreen), pixel.z()*(255/maxBlue));
        }
        else{
            newColor.setRgb(pixel.x(), pixel.y(), pixel.z());
        }
        image.setPixel((i/_camera->size().first),(i%_camera->size().first),newColor.rgb());
        i++;
    }
    
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    qDebug() << "Set pixel color:       Elapsed time: " 
             << elapsed_seconds.count() << "s";
    return image;
}

