#include <mutex>
#include <thread>
#include <QDebug>
#include "renderer.hpp"

Renderer::Renderer():
    available_cpu_threads_(std::thread::hardware_concurrency())
{
    if (available_cpu_threads_ < 1)
        available_cpu_threads_ = 1;
}

point3D Renderer::GetPixel(Scene & scene,
                           const int i,
                           const int j)
{
    point3D imgPlaneIntersect(scene.GetCamera().resolution().first * (i-(scene.GetCamera().size().first/2)),
                              scene.GetCamera().resolution().second * (j-(scene.GetCamera().size().second/2)),
                              0);

    point3D rayDirection = imgPlaneIntersect - scene.GetFocalPoint();
    rayDirection = rayDirection.norm();
    double minDistance = std::numeric_limits<double>::max();
    int interest = -1;
    point3D shadowRay, intersection, normal, intersection2, normal2;
    bool objecthit = false;

    //this loop detects of the ray intersects an object
    //and when multiple objects,
    //finds the closest.
    int k = 0;
    for(auto object : scene.GetObjects()){
        if(object->intersects(scene.GetFocalPoint(), rayDirection, intersection, normal)){

            double distance = sqrt((intersection - scene.GetFocalPoint()).dot(intersection - scene.GetFocalPoint()));
            if(distance < minDistance){
                minDistance = distance;
                interest = k;
                intersection2 = intersection;
                normal2 = normal;
                objecthit = true;
            }
        }
        k++;
    }
    point3D pixColor(0,0,0);
    if(objecthit) {

        for(auto light : scene.GetLights()){

            //determine if there is another object blocking the light
            bool shaded = false;
            shadowRay = (light->location() - intersection2).norm();
            if(shadowRay.dot(normal2) > 0){
                point3D trash1;
                point3D trash2;

                auto objects = scene.GetObjects();
                for(int l = 0; l < objects.size() && shaded == false; l++){
                    //test for intersection with other objects
                    if(objects[l]->intersects(intersection2, shadowRay, trash1, trash2)){
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
                    point3D colors(objects[interest]->color().red(),
                                   objects[interest]->color().green(),
                                   objects[interest]->color().blue());

                    pixColor = pixColor + colors * light->intensity() * scale;
                }//end color loop
            }//end loop through lights
        }
    }//end object shading effects

    return pixColor;
}


void Renderer::GetRange(int start_pix,
                        int finish_pix,
                        Scene & scene,
                        std::vector<point3D> & pixMatrix)
{
    std::mutex m;
    auto row_length = scene.GetCamera().size().first;
    for (int i = start_pix; i < finish_pix; i++){
        auto value = GetPixel(scene, i/row_length, i%row_length);
        std::lock_guard<std::mutex> lk(m);
        pixMatrix[i] = value;
    }
}

QImage Renderer::RenderOnCpu(Scene & scene)
{
    QImage image(scene.GetCamera().size().first,
                 scene.GetCamera().size().second,
                 QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::black);
    std::vector<point3D> pixMatrix;
    pixMatrix.assign(scene.GetCamera().size().first * scene.GetCamera().size().second,
                     point3D(0,0,0));
    double maxRed = 0;
    double maxGreen = 0;
    double maxBlue = 0;

    std::chrono::time_point<std::chrono::system_clock>start, end;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
    std::vector<std::thread> threads;
    int start_pix = 0;
    int finish_pix = pixMatrix.size()/available_cpu_threads_;
    int range = finish_pix;
    for (int i = 0; i < available_cpu_threads_; i++) {
        threads.push_back(std::thread(&Renderer::GetRange,
                                      start_pix,
                                      finish_pix,
                                      std::ref(scene),
                                      std::ref(pixMatrix)
                                      ));
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
        image.setPixel((i / scene.GetCamera().size().first),
                       (i % scene.GetCamera().size().first),
                       newColor.rgb());
        i++;
    }

    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    qDebug() << "returning image";
    return image;
}
