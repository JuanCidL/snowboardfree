
#include <rusty_audio.h>
#include <string>
#include <vector>
#include <ciso646>
#include <cmath>
#include <random>
#include <nothofagus.h>
#include "piano.h"

int main()
{
    constexpr unsigned int sampleRate = 48000;
    constexpr unsigned int channels = 2;

    const Piano::Key& key = Piano::Key::getInstance();

    RustyAudio::Builder soundBuilder;
    soundBuilder.appendSinusoids({
        {100, 0.5, key.getKey("C1")},
        // {500, 0.5, 700},
        // {300, 0.5, 600},
        // {100, 0.5, 600},
        // {500, 0.5, 700},
        // {300, 0.5, 600},
        // {100, 0.5, 600},
        // {500, 0.5, 700},
        // {300, 0.5, 600},
    });

    RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    RustyAudio::Player soundPlayer;
    soundPlayer.init(soundBuffer);

    // Nothofagus
    Nothofagus::Canvas canvas({ 150, 100 }, "Hello Text", { 0.7, 0.7, 0.7 }, 6);

    Nothofagus::ColorPallete pallete1{
        {0.0, 0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0, 1.0},
        {1.0, 1.0, 0.0, 0.7},
        {0.0, 1.0, 1.0, 0.7},
        {1.0, 1.0, 1.0, 0.7}
    };
    pallete1 *= 0.5;
    pallete1 += glm::vec3(0.0, 0.5, 0.0);

    Nothofagus::ColorPallete pallete2{
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };

    Nothofagus::ColorPallete pallete3{
        {0.0, 0.0, 0.0, 0.8},
        {1.0, 1.0, 1.0, 1.0 }
    };

    Nothofagus::Texture texture1({ 15, 10 }, { 0.5, 0.5, 0.5, 1.0 });
    texture1.setPallete(pallete1);
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, pallete1.size() - 1);

        for (std::size_t i = 0; i < texture1.size().x; ++i)
        {
            for (std::size_t j = 0; j < texture1.size().y; ++j)
            {
                const Nothofagus::Pixel randomColor{ dist(rng) };
                texture1.setPixel(i, j, randomColor);
            }
        }
    }

    Nothofagus::TextureId textureId1 = canvas.addTexture(texture1);

    Nothofagus::Texture texture2({ 8, 8 }, { 0.5, 0.5, 0.5, 1.0 });
    texture2.setPallete(pallete2);
    Nothofagus::writeChar(texture2, 0xD, 0, 0, Nothofagus::FontType::Hiragana);
    Nothofagus::TextureId textureId2 = canvas.addTexture(texture2);

    std::string text = "- Nothofagus -";
    Nothofagus::Texture texture3({ 8 * text.size(), 8 }, { 0.5, 0.5, 0.5, 1.0 });
    texture3.setPallete(pallete3);
    Nothofagus::writeText(texture3, text);
    Nothofagus::TextureId textureId3 = canvas.addTexture(texture3);

    // -1 will set the bellota at the back, so it does not draw over the other bellotas.
    Nothofagus::BellotaId bellotaId1 = canvas.addBellota({ {{75.0f, 50.0f}, 10.0}, textureId1, -1 });

    // if you don't specify the offset, it is 0, the drawing order will be implementation defined.
    Nothofagus::BellotaId bellotaId2 = canvas.addBellota({ {{75.0f, 90.0f}}, textureId2 });
    Nothofagus::BellotaId bellotaId3 = canvas.addBellota({ {{75.0f, 50.0f}}, textureId3 });

    float time = 0.0f;
    bool rotate = true;
    bool visible = true;


    // tatatatatatatata

    Nothofagus::ColorPallete palleteRGB{
        {1.0, 0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0, 1.0},
        {0.0, 0.0, 1.0, 1.0}
    };

    Nothofagus::Texture textureRGB({ 9, 1 }, { 0.5, 0.5, 0.5, 1.0 });
    textureRGB.setPallete(palleteRGB);


    for (std::size_t i = 0; i < textureRGB.size().x; ++i)
    {
        const Nothofagus::Pixel randomColor{ i / palleteRGB.size() };
        textureRGB.setPixel(i, 0, randomColor);
    }
    
    Nothofagus::TextureId textureIdRGB = canvas.addTexture(textureRGB);
    Nothofagus::BellotaId bellotaIdRGB = canvas.addBellota({{{75.0f, 10.0f}}, textureIdRGB});

    auto update = [&](float dt)
        {
            time += dt;

            Nothofagus::Bellota& bellota3 = canvas.bellota(bellotaId3);
            bellota3.transform().angle() = 5.0f * std::sin(0.005f * time);

            Nothofagus::Bellota& bellotaRGB = canvas.bellota(bellotaIdRGB);
            bellotaRGB.transform().scale().y = 2.0f + 1.5f * std::sin(0.01f * time);
            bellotaRGB.transform().angle() = 5.0f * std::sin(0.005f * time);
        };

    soundPlayer.setLooping(true);
    soundPlayer.play();

    canvas.run(update);
    
    return 0;
}