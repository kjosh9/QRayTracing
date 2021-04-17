#ifndef PARSE_HPP
#define PARSE_HPP

#include <QString>
#include <vector>

#include "light.hpp"
#include "shadedObject.hpp"
#include "camera.hpp"

namespace parser {

bool parse(std::string filename,
           Camera & camera,
           std::vector<Light*> & lights,
           std::vector<ShadedObject*> & objects);

}
#endif // PARSE_HPP
