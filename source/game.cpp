#include "game.h"

namespace Game {

bool paused = false;

std::unordered_map<std::string, std::unique_ptr<RustyAudio::Player>> sounds;

Nothofagus::BellotaId pauseBackgroundBellotaId = { 0 };
Nothofagus::BellotaId pauseTextBellotaId = { 0 };
Nothofagus::BellotaId resumeTextBellotaId = { 0 };
Nothofagus::BellotaId restartTextBellotaId = { 0 };

const unsigned int CANVAS_WIDTH = 896;
const unsigned int CANVAS_HEIGHT = 504;

const glm::vec2 playerPosition = {CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 100};
glm::vec2 velocity{ 0.0f, 0.0f };

Nothofagus::Canvas canvas({ Game::CANVAS_WIDTH, Game::CANVAS_HEIGHT }, "SnowboardFree", { 0.7, 0.7, 0.7 }, 1);

std::vector<Sign> signs = {
    Sign({ 150, 400 }, "Move with A, S and D"),
    Sign({ 750, 300 }, "Press ENTER to pause"),
    Sign({ 170, 280 }, "Press ESC to exit"),
};

Nothofagus::Controller controller;

Entity::PlayerEntity player;

Entity::Yeti yeti({ 100, 100 });

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
    Nothofagus::Texture backgroundTexture({ Game::CANVAS_WIDTH, Game::CANVAS_HEIGHT }, { 1.0f, 1.0f, 1.0f, 1.0f });
    Nothofagus::TextureId backgroundTextureId = Game::canvas.addTexture(backgroundTexture);
    Nothofagus::BellotaId backgoundBellotaId = Game::canvas.addBellota({ {{Game::CANVAS_WIDTH/2, Game::CANVAS_HEIGHT/2}}, backgroundTextureId, 0});

    setupController();
    setupPause();
    setupEntities();
}

void setupController()
{
    controller.registerAction({ Nothofagus::Key::ENTER, Nothofagus::DiscreteTrigger::Press }, [&]()
    {
        paused = !paused; 
        if (paused) showPause();
        else hidePause();
    });
    controller.registerAction({ Nothofagus::Key::W, Nothofagus::DiscreteTrigger::Press }, [&]()
    {
        if (paused){
            hidePause();
            restart();
        }
    });
    controller.registerAction({ Nothofagus::Key::ESCAPE, Nothofagus::DiscreteTrigger::Press }, [&]()
    {
        canvas.close();
    });

    Game::player.setupController(controller);
}

void setupEntities()
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

void setupPause()
{
    Nothofagus::ColorPallete pausePallete{
        {0.0, 0.0, 0.0, 0.8},
        {1.0, 1.0, 1.0, 1.0 }
    };

    Nothofagus::Texture pauseTexture({ CANVAS_WIDTH/2, CANVAS_HEIGHT/2 }, { 0.0f, 0.0f, 0.0f, 0.8f });
    pauseTexture.setPallete(pausePallete);
    Nothofagus::TextureId pauseTextureId = Game::canvas.addTexture(pauseTexture);
    pauseBackgroundBellotaId = Game::canvas.addBellota({ {{ CANVAS_WIDTH/2, CANVAS_HEIGHT/2}}, pauseTextureId, -1});

    const std::string pauseText = "PAUSED";
    Nothofagus::Texture pauseTextTexture({ 8 * pauseText.size(), 8 }, { 0.0f, 0.0f, 0.0f, 0.8f });
    pauseTextTexture.setPallete(pausePallete);
    Nothofagus::writeText(pauseTextTexture, "PAUSED");
    Nothofagus::TextureId pauseTextTextureId = Game::canvas.addTexture(pauseTextTexture);
    pauseTextBellotaId = Game::canvas.addBellota({ {{ CANVAS_WIDTH/2, CANVAS_HEIGHT/2 + 16}}, pauseTextTextureId, -1});
    const std::string resumeText = "Press ENTER to resume";
    Nothofagus::Texture resumeTextTexture({ 8 * resumeText.size(), 8 }, { 0.0f, 0.0f, 0.0f, 0.8f });
    resumeTextTexture.setPallete(pausePallete);
    Nothofagus::writeText(resumeTextTexture, "Press ENTER to resume");
    Nothofagus::TextureId resumeTextTextureId = Game::canvas.addTexture(resumeTextTexture);
    resumeTextBellotaId = Game::canvas.addBellota({ {{ CANVAS_WIDTH/2, CANVAS_HEIGHT/2 }}, resumeTextTextureId, -1});
    const std::string restartText = "Press W to restart";
    Nothofagus::Texture restartTextTexture({ 8 * restartText.size(), 8 }, { 0.0f, 0.0f, 0.0f, 0.8f });
    restartTextTexture.setPallete(pausePallete);
    Nothofagus::writeText(restartTextTexture, "Press W to restart");
    Nothofagus::TextureId restartTextTextureId = Game::canvas.addTexture(restartTextTexture);
    restartTextBellotaId = Game::canvas.addBellota({ {{ CANVAS_WIDTH/2, CANVAS_HEIGHT/2 - 16}}, restartTextTextureId, -1});
}

void setupGui()
{
    ImGui::Begin("Stats");
    ImGui::Text("Player velocity: %i", (int) velocity.y);
    ImGui::End();
}

void showPause()
{
    Game::canvas.bellota(Game::pauseBackgroundBellotaId).depthOffset() = 14;
    Game::canvas.bellota(Game::pauseTextBellotaId).depthOffset() = 15;
    Game::canvas.bellota(Game::resumeTextBellotaId).depthOffset() = 15;
    Game::canvas.bellota(Game::restartTextBellotaId).depthOffset() = 15;
}

void hidePause()
{
    Game::canvas.bellota(Game::pauseBackgroundBellotaId).depthOffset() = -1;
    Game::canvas.bellota(Game::pauseTextBellotaId).depthOffset() = -1;
    Game::canvas.bellota(Game::resumeTextBellotaId).depthOffset() = -1;
    Game::canvas.bellota(Game::restartTextBellotaId).depthOffset() = -1;
}

void restart()
{
    paused = false;
    velocity = { 0.0f, 0.0f };
    for (auto& sign : signs)
        sign.reset();
    for (auto& ramp : ramps)
        ramp.reset();
    for (auto& tree : trees)
        tree.reset();
}

void update(float dt)
{
    if (paused) return;
    player.update(dt);
    for (auto& sign : signs)
        sign.update(dt);
    for (auto& ramp : ramps)
    {
        ramp.update(dt);
        if (ramp.checkCollision(player))
            player.jump();
    }
    for (auto& tree : trees)
    {
        tree.update(dt);
        if (tree.checkCollision(player))
        {
            tree.canCollide = false;
            player.crash();
        }
    }
}

} 