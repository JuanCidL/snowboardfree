#include "entity.h"
#include "game.h"

namespace Entity
{

Entity::Entity(): canCollide(true) {};

bool Entity::checkCollision(const Entity& other) const 
{
    if (!canCollide || !other.canCollide)
    {
        return false;
    }
    return (
        position().x + boundingBox().leftBottomCorner().x < other.position().x + other.boundingBox().rightTopCorner().x &&
        position().x + boundingBox().rightTopCorner().x > other.position().x + other.boundingBox().leftBottomCorner().x &&
        position().y + boundingBox().leftBottomCorner().y < other.position().y + other.boundingBox().rightTopCorner().y &&
        position().y + boundingBox().rightTopCorner().y > other.position().y + other.boundingBox().leftBottomCorner().y
    );
};
const glm::vec2& Entity::position() const { return _position; };

const BoundingBox& Entity::boundingBox() const { return _boundingBox; };

void Entity::update(float dt) {};

}