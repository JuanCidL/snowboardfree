#pragma once
#include "entity.h"

namespace Entity
{

class Yeti : public AnimatedEntity
{

public:
    Yeti(glm::vec2 position);

    void update(float dt) override;
    void reset() override;
    void eat();

private:
    glm::vec2 pos;
    float stepTime;
    float stepDuration;
    bool walking;
    float walkSpeed;
    glm::vec2 walkDirection;
    bool eating;
    float eatTime;
    float eatDuration;
    void walk(float dt);
    void eatAnim(float dt);
};

}