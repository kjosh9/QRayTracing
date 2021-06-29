#include <mutex>
#include <thread>
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
                for(int l = 0; l < objects.size(); l++){
                    //test for intersection with other objects
                    if(objects[l]->intersects(intersection2, shadowRay, trash1, trash2)){
                        if(trash1.z() > 0){
                            shaded = true;
                            break;
                        }
                    }
                }
                if(!shaded){
                    double scale = normal2.dot(shadowRay.norm());
                    if (scale < 0){
                        scale *= -1;
                    }
                    point3D colors(objects[interest]->color().red,
                                   objects[interest]->color().green,
                                   objects[interest]->color().blue);

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

std::vector<point3D> Renderer::RenderOnCpu(Scene & scene, const int thread_count)
{
    std::vector<point3D> pixMatrix;
    pixMatrix.assign(scene.GetCamera().size().first * scene.GetCamera().size().second,
                     point3D(0,0,0));
    double maxRed = 0;
    double maxGreen = 0;
    double maxBlue = 0;

    std::vector<std::thread> threads;
    int start_pix = 0;
    int finish_pix = pixMatrix.size()/thread_count;
    int range = finish_pix;
    for (int i = 0; i < thread_count; i++) {
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

    if (maxRed > 255 || maxBlue > 255 || maxGreen > 255) {
        for(point3D & pixel: pixMatrix) {
            pixel.set_x(pixel.x()*(255/maxRed));
            pixel.set_y(pixel.y()*(255/maxGreen));
            pixel.set_z(pixel.z()*(255/maxBlue));
        }
    }

    return pixMatrix;
}
