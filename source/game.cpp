#include "game.h"

namespace Game {

const unsigned int CANVAS_WIDTH = 896;
const unsigned int CANVAS_HEIGHT = 504;

const glm::vec2 playerPosition = {CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 100};
glm::vec2 velocity{ 0.0f, 0.0f };

Nothofagus::Canvas canvas({ Game::CANVAS_WIDTH, Game::CANVAS_HEIGHT }, "Hello Text", { 0.7, 0.7, 0.7 }, 2);

Entity::PlayerEntity player;

int rampCount = 20;
std::vector<Entity::Ramp> ramps;
int treeCount = 30;
std::vector<Entity::Tree> trees;

float minX = -896*2;
float maxX = 896*2;
float minY = -(504 + 504 / 2.0f);
float maxY = 0;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> disX(minX, maxX);
std::uniform_real_distribution<float> disY(minY, maxY);

void setup()
{
    ramps.reserve(rampCount);
    for (int i = 0; i < rampCount; i++)
    {
        Entity::Ramp ramp({ disX(gen), disY(gen) });
        ramps.emplace_back(ramp);
    }
    trees.reserve(treeCount);
    for (int i = 0; i < treeCount; i++)
    {
        Entity::Tree tree({ disX(gen), disY(gen) });
        trees.emplace_back(tree);
    }

}

void update(float dt)
{
    for (auto& ramp : ramps)
    {
        ramp.update(dt);
        if (ramp.checkCollision(player))
        {
            std::cout << "Collision detected" << std::endl;
            player.jump();
        }
    }
    for (auto& tree : trees)
    {
        tree.update(dt);
        if (tree.checkCollision(player))
        {
            std::cout << "Collision detected" << std::endl;
            tree.canCollide = false;
            player.crash();
        }
    }
}

} 