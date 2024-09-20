#pragma once
#include "entity.h"

namespace Entity
{


class PlayerEntity : public AnimatedEntity
{
public:
    PlayerEntity();
    
    void setupController(Nothofagus::Controller& controller);

    void update(float dt) override;
private:
    bool leftKeyPressed;
    bool rightKeyPressed;
    bool downKeyPressed;
    glm::vec2 maxVelocity;
    float acceleration;
    float deceleration;
};

}