#pragma once
#include <nothofagus.h>
#include <vector>
#include <random>
#include "player.h"
#include "obstacles.h"

namespace Game{

extern const unsigned int CANVAS_WIDTH ;
extern const unsigned int CANVAS_HEIGHT ;
extern const glm::vec2 playerPosition ;
extern glm::vec2 velocity;

extern Nothofagus::Canvas canvas;

extern Entity::PlayerEntity player;

extern int rampCount;
extern std::vector<Entity::Ramp> ramps;
extern int treeCount;
extern std::vector<Entity::Tree> trees;

extern float minX;
extern float maxX;
extern float minY;
extern float maxY;

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> disX;
extern std::uniform_real_distribution<float> disY;

extern void setup();

extern void update(float dt);

}