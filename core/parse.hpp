#ifndef PARSE_HPP
#define PARSE_HPP

#include <QString>
#include <QVector>

#include "light.hpp"
#include "shadedObject.hpp"
#include "camera.hpp"

namespace parser {

bool parse(QString filename,
           Camera & camera,
           QVector<Light*> & lights,
           QVector<ShadedObject*> & objects);

}
#endif // PARSE_HPP
