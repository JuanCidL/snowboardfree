
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

    
    float time = 0.0f;

    Game::setup();

    auto update = [&](float dt)
        {
            time += dt;
            std::cout<<Game::velocity.y<<std::endl;
            Game::update(dt);
            Game::setupGui();
        };

    /*soundPlayer.setLooping(true);
    soundPlayer.play();*/

    Game::canvas.run(update, Game::controller);
    
    return 0;
}