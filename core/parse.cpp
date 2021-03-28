#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include "parse.hpp"
#include "plane.hpp"
#include "sphere.hpp"

namespace parser {

bool parse(QString filename,
           Camera & camera,
           QVector<Light*> & lights,
           QVector<ShadedObject*> & objects)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QString contents = file.readAll();
    file.close();

    QJsonDocument JSonDoc = QJsonDocument::fromJson(contents.toUtf8());
    qWarning() << JSonDoc.isNull();

    QJsonObject JSonObj;
    JSonObj = JSonDoc.object();
    qDebug() << JSonObj;

    QStringList keysList = JSonObj.keys();
    if(!(keysList.contains("camera") && keysList.contains("lights") && keysList.contains("objects"))){
        return false;
        qDebug() << "Error: Improper JSON file";
    }
    for(int i = 0; i < keysList.size(); i++){
        if(keysList[i] == "camera"){
            QJsonObject newObj = JSonObj[keysList[i]].toObject();

            point3D center, normal;
            //do all the parameters here
            int focus = newObj["focus"].toInt();
            QJsonObject centerJS = newObj["center"].toObject();
            if(centerJS.contains("x") && centerJS.contains("y") && centerJS.contains("z")){
                center = point3D(centerJS["x"].toDouble(),
                        centerJS["y"].toDouble(),
                        centerJS["z"].toDouble());
            }
            else{
                return false;
            }

            QJsonObject normalJS = newObj["normal"].toObject();
            if(normalJS.contains("x") && normalJS.contains("y") && normalJS.contains("z")){
                normal = point3D(normalJS["x"].toDouble(),
                        normalJS["y"].toDouble(),
                        normalJS["z"].toDouble());
            }
            else{
                qDebug() << "Error: Improper JSON file";
                return false;
            }

            QJsonArray resArray = newObj["resolution"].toArray();
            QPair<double, double> resol;
            resol.first = resArray.at(0).toDouble();
            resol.second = resArray.at(1).toDouble();

            QJsonArray sizeArray = newObj["size"].toArray();
            QPair<int, int> camSize;
            camSize.first = sizeArray.at(0).toInt();
            camSize.second = sizeArray.at(1).toInt();


            camera = Camera(center, normal, focus, camSize, resol);
        }
        else if(keysList[i] == "lights"){
            QJsonArray lightsArray = JSonObj[keysList[i]].toArray();
            qDebug() << "make lights";

            for(int j = 0; j < lightsArray.size(); j++){

                QJsonObject newLightJS = lightsArray.at(j).toObject();

                double intensity = newLightJS["intensity"].toDouble();

                QJsonObject locat = newLightJS["location"].toObject();
                point3D location = point3D(locat["x"].toDouble(),
                        locat["y"].toDouble(),
                        locat["z"].toDouble());

                //make sure to place this in a vector or list
                Light* newLight = new Light(intensity, location);
                lights.append(newLight);
            }
        }
        else{
            QJsonArray objectsArray = JSonObj[keysList[i]].toArray();
            qDebug() << "make shaded object";
            for(int j = 0; j < objectsArray.size(); j++){

                QJsonObject newObjectJS = objectsArray.at(j).toObject();
                double lambert = newObjectJS["lambert"].toDouble();

                QJsonObject locat = newObjectJS["center"].toObject();
                point3D location = point3D(locat["x"].toDouble(),
                        locat["y"].toDouble(),
                        locat["z"].toDouble());

                QJsonObject colorJS = newObjectJS["color"].toObject();

                QColor color;
                if (colorJS["r"].toInt() < 256 &&
                    colorJS["g"].toInt() < 256 &&
                    colorJS["b"].toInt() < 256) {

                    color.setRgb(colorJS["r"].toInt(),
                                 colorJS["g"].toInt(),
                                 colorJS["b"].toInt(),
                                 255);
                }
                else{
                    qDebug() << "Incorrect color";
                    return false;
                }

                if(newObjectJS["type"] == "sphere"){
                    double radius = newObjectJS["radius"].toDouble();
                    Sphere* newSphere = new Sphere(lambert, location, color, radius);
                    objects.append(newSphere);
                }
                else if(newObjectJS["type"] == "plane"){
                    QJsonObject norm = newObjectJS["center"].toObject();
                    point3D normal = point3D(norm["x"].toDouble(),
                            norm["y"].toDouble(),
                            norm["z"].toDouble());
                    Plane* newPlane = new Plane(lambert, location, color, normal);
                    objects.append(newPlane);
                }
            }
        }
    }
    return true;
}

} //parser
