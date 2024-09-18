#include "entity.h"
#pragma once

namespace Entity
{

enum PlayerState
{
    IDLE,
    Left,
    LeftDown,
    Right,
    RightDown,
    Down,
};

class PlayerEntity : public AnimatedEntity
{
public:
    PlayerEntity(
        Nothofagus::Canvas& canvas, glm::vec2 position);
    
    void setupController(Nothofagus::Controller& controller);

    void update(Nothofagus::Canvas& canvas, float dt);
private:
    int state;
    bool updated;
};

}