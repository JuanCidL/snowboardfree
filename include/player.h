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

    void jump();
    
    void crash();

private:
    bool leftKeyPressed;
    bool rightKeyPressed;
    bool downKeyPressed;
    glm::vec2 maxVelocity;
    float acceleration;
    float deceleration;
    bool isJumping;
    float maxJumpVelocity;
    float jumpHeight;
    float crashTime;
    float crashDuration;
};

}