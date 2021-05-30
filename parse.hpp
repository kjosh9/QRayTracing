#ifndef PARSE_HPP
#define PARSE_HPP

#include <QString>
#include <vector>

#include "core/light.hpp"
#include "core/shadedObject.hpp"
#include "core/camera.hpp"

namespace parser {

bool parse(std::string filename,
           Camera & camera,
           std::vector<Light*> & lights,
           std::vector<ShadedObject*> & objects);

}
#endif // PARSE_HPP
