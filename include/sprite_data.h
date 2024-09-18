#include <nothofagus.h>
#include <string>
#include <unordered_map>
#include <initializer_list>

namespace SpriteData {

typedef struct {
    glm::ivec2 dimensions;
    std::initializer_list<glm::vec4> spriteColors;
    std::initializer_list<std::uint8_t> spritePixels;
} SpriteData;   

class Sprite{
public:
    Sprite(SpriteData spriteData);

    void setup(Nothofagus::Canvas& canvas, glm::vec2 position);

    const Nothofagus::TextureId getTextureId() const { return this->textureId; }
    const Nothofagus::BellotaId getBellotaId() const{ return this->bellotaId; }

private:
    SpriteData spriteData;
    Nothofagus::Texture *texture;
    Nothofagus::TextureId textureId;
    Nothofagus::BellotaId bellotaId;
};



}