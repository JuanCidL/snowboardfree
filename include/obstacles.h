#pragma once
#include "entity.h"

namespace Entity
{

enum class Obstacle
{
    Ramp,
    Tree
};

class Ramp: public StaticEntity
{
public:
    Ramp(glm::vec2 position);
};

class Tree: public StaticEntity
{
public:
    Tree(glm::vec2 position);
};

}