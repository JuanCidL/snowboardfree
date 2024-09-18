#include <nothofagus.h>
#pragma once

namespace Entity
{

class Entity
{
public:
    Entity(glm::ivec2 dimensions, glm::vec2 position);


    const glm::vec2 position() const { return _position; }
    glm::vec2& position() { return _position; }


protected:
    glm::vec2 _position;
    glm::ivec2 _dimensions;
};


class AnimatedEntity : public Entity
{
public:
    AnimatedEntity(
        Nothofagus::Canvas& canvas,
        glm::ivec2 dimensions, glm::vec2 position,
        std::initializer_list<glm::vec4> colors,
        std::initializer_list<std::initializer_list<std::uint8_t>> sprites);


protected:
    glm::vec2 position;
    glm::ivec2 dimensions;
    std::vector<Nothofagus::BellotaId> bellotaIds;
    Nothofagus::BellotaId currentBellotaId;
};


}