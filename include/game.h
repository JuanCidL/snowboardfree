#pragma once
#include <nothofagus.h>
#include <vector>
#include <random>
#include <string>
#include "piano.h"
#include "player.h"
#include "yeti.h"
#include "obstacles.h"
#include "sign.h"


namespace Game{

extern bool paused;
extern bool end;

extern Nothofagus::BellotaId pauseBackgroundBellotaId;
extern Nothofagus::BellotaId pauseTextBellotaId;
extern Nothofagus::BellotaId resumeTextBellotaId;
extern Nothofagus::BellotaId restartTextBellotaId;

extern float ellapsedTime;
extern int gameTime;

extern const unsigned int CANVAS_WIDTH ;
extern const unsigned int CANVAS_HEIGHT ;

extern const glm::vec2 playerPosition ;
extern glm::vec2 velocity;

extern Nothofagus::Canvas canvas;

extern std::vector<Sign> signs;

extern Nothofagus::Controller controller;

extern Entity::PlayerEntity player;

extern Entity::Yeti yeti;

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
extern std::uniform_int_distribution<int> disGameTime;

extern void setup();
extern void setupSounds();
extern void setupController();
extern void setupEntities();
extern void setupPause();
extern void setupGui();
extern void showPause();
extern void hidePause();

extern void restart();

extern void update(float dt);

}