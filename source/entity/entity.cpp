#include "entity.h"

namespace Entity
{

Entity::Entity(glm::ivec2 dimensions, glm::vec2 position) :
    _position(position),
    _dimensions(dimensions)        
    {};

}