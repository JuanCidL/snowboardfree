
#include <rusty_audio.h>
#include <string>
#include <vector>
#include <ciso646>
#include <cmath>
#include <random>
#include <nothofagus.h>
#include <string>
#include "piano.h"
#include "player.h"
#include "obstacles.h"
#include "game.h"

int main()
{
    //constexpr unsigned int sampleRate = 48000;
    //constexpr unsigned int channels = 2;

    //const Piano::Key& key = Piano::Key::getInstance();

    //RustyAudio::Builder soundBuilder;
    //soundBuilder.appendSinusoids({
    //    {100, 0.5, key.getKey("C1")},
    //    // {500, 0.5, 700},
    //    // {300, 0.5, 600},
    //    // {100, 0.5, 600},
    //    // {500, 0.5, 700},
    //    // {300, 0.5, 600},
    //    // {100, 0.5, 600},
    //    // {500, 0.5, 700},
    //    // {300, 0.5, 600},
    //});

    //RustyAudio::Buffer soundBuffer = soundBuilder.generate(sampleRate, channels);

    //RustyAudio::Player soundPlayer;
    //soundPlayer.init(soundBuffer);

    // Nothofagus

    Nothofagus::Controller controller;

    Game::player.setupController(controller);

    Nothofagus::Texture backgroundTexture({ Game::CANVAS_WIDTH, Game::CANVAS_HEIGHT }, { 1.0f, 1.0f, 1.0f, 1.0f });
    Nothofagus::TextureId backgroundTextureId = Game::canvas.addTexture(backgroundTexture);
    Nothofagus::BellotaId backgoundBellotaId = Game::canvas.addBellota({ {{Game::CANVAS_WIDTH/2, Game::CANVAS_HEIGHT/2}}, backgroundTextureId, 0});

    float time = 0.0f;

    Game::setup();

    auto update = [&](float dt)
        {
            time += dt;

            // Nothofagus::Bellota& bellota3 = canvas.bellota(bellotaId3);
            // bellota3.transform().angle() = 5.0f * std::sin(0.005f * time);

            // Nothofagus::Bellota& bellotaRGB = canvas.bellota(bellotaIdRGB);
            // bellotaRGB.transform().scale().y = 2.0f + 1.5f * std::sin(0.01f * time);
            // bellotaRGB.transform().angle() = 5.0f * std::sin(0.005f * time);
            Game::player.update(dt);
            std::cout<<Game::velocity.y<<std::endl;
            Game::update(dt);
        };

    /*soundPlayer.setLooping(true);
    soundPlayer.play();*/

    Game::canvas.run(update, controller);
    
    return 0;
}