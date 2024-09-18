#include "entity.h"

namespace Entity
{

AnimatedEntity::AnimatedEntity(
    Nothofagus::Canvas& canvas,
    glm::ivec2 dimensions, glm::vec2 position,
    std::initializer_list<glm::vec4> colors,
    std::initializer_list<std::initializer_list<std::uint8_t>> sprites):
    Entity(dimensions, position)
{
    Nothofagus::ColorPallete colorPallete(colors);
    for(auto sprite : sprites)
    {
        Nothofagus::Texture texture = {dimensions, {0.0, 0.0, 0.0, 0.0}};
        texture.setPallete(colorPallete).setPixels(sprite);
        Nothofagus::TextureId textureId = canvas.addTexture(texture);
        Nothofagus::BellotaId bellotaId = canvas.addBellota({position, textureId, -1});
        this->bellotaIds.push_back(bellotaId);
    }
    this->currentBellotaId = this->bellotaIds[0];
    canvas.bellota(this->currentBellotaId).depthOffset() = 1;
};

}
