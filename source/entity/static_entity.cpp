#include "entity.h"
#include "game.h"

namespace Entity
{

StaticEntity::StaticEntity(
    glm::ivec2 dimensions, glm::vec2 position,
    std::initializer_list<glm::vec4> colors,
    std::initializer_list<std::uint8_t> sprite):
    Entity()
{
    Nothofagus::ColorPallete colorPallete(colors);
    Nothofagus::Texture texture = {dimensions, {0.0, 0.0, 0.0, 0.0}};
    texture.setPallete(colorPallete).setPixels(sprite);
    Nothofagus::TextureId textureId = Game::canvas.addTexture(texture);
    Nothofagus::BellotaId bellotaId = Game::canvas.addBellota({position, textureId, -1});
    this->bellotaId = bellotaId;
    Game::canvas.bellota(this->bellotaId).depthOffset() = 2;
};

const glm::vec2& StaticEntity::position() const
{
    return Game::canvas.bellota(this->bellotaId).transform().location();
};

void StaticEntity::reset()
{
    Game::canvas.bellota(this->bellotaId).transform().location().x = Game::disX(Game::gen);
    Game::canvas.bellota(this->bellotaId).transform().location().y = Game::disY(Game::gen);
    canCollide = true;
};

void StaticEntity::update(float dt)
{
    auto& bellota = Game::canvas.bellota(this->bellotaId);
    bellota.transform().location() += Game::velocity * dt / 50.0f;

    if (bellota.transform().location().y > Game::CANVAS_HEIGHT+64)
    {
        bellota.transform().location().x = Game::disX(Game::gen);
        bellota.transform().location().y = Game::disY(Game::gen);
        canCollide = true;
    }
};


}