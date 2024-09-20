#include "entity.h"
#include "game.h"

namespace Entity
{

AnimatedEntity::AnimatedEntity(
    glm::ivec2 dimensions, glm::vec2 position,
    std::initializer_list<glm::vec4> colors,
    std::initializer_list<std::initializer_list<std::uint8_t>> sprites):
    Entity()
{
    Nothofagus::ColorPallete colorPallete(colors);
    for(auto sprite : sprites)
    {
        Nothofagus::Texture texture = {dimensions, {0.0, 0.0, 0.0, 0.0}};
        texture.setPallete(colorPallete).setPixels(sprite);
        Nothofagus::TextureId textureId = Game::canvas.addTexture(texture);
        Nothofagus::BellotaId bellotaId = Game::canvas.addBellota({position, textureId, -1});
        this->bellotaIds.push_back(bellotaId);
    }
    this->currentBellotaId = this->bellotaIds[0];
    Game::canvas.bellota(this->currentBellotaId).depthOffset() = 1;
};

const glm::vec2& AnimatedEntity::position() const
{
    return Game::canvas.bellota(this->currentBellotaId).transform().location();
};

void AnimatedEntity::update(float dt){};

}
