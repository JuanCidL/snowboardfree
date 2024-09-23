
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
    // Jump sound
    RustyAudio::Builder jumpSoundBuilder;
    jumpSoundBuilder.appendSinusoids({
        {50, 0.3, Piano::keys["C3"]},
        {30, 0.3, Piano::keys["E3"]},
        {20, 0.3, Piano::keys["G3"]},
        {40, 0.3, Piano::keys["C4"]},
        {60, 0.3, Piano::keys["E4"]},
        {70, 0.3, Piano::keys["G4"]},
    });
    RustyAudio::Buffer jumpSoundBuffer = jumpSoundBuilder.generate(Piano::sampleRate, Piano::channels);
    auto jumpSoundPlayer = std::make_unique<RustyAudio::Player>();
    jumpSoundPlayer->init(jumpSoundBuffer);
    Piano::addSound("jump", std::move(jumpSoundPlayer));

    // Crash sound
    RustyAudio::Builder crashSoundBuilder;
    crashSoundBuilder.appendSinusoids({
        {30, 0.3, Piano::keys["G4"]},
        {20, 0.3, Piano::keys["E4"]},
        {10, 0.3, Piano::keys["C4"]},
        {20, 0.3, Piano::keys["G3"]},
        {20, 0.3, Piano::keys["E3"]},
        {30, 0.3, Piano::keys["C3"]},
    });
    RustyAudio::Buffer crashSoundBuffer = crashSoundBuilder.generate(Piano::sampleRate, Piano::channels);
    auto crashSoundPlayer = std::make_unique<RustyAudio::Player>();
    crashSoundPlayer->init(crashSoundBuffer);
    Piano::addSound("crash", std::move(crashSoundPlayer));
    


    
    float time = 0.0f;

    Game::setup();

    // Game::piano.playSound("jump");

    auto update = [&](float dt)
        {
            time += dt;
            Game::update(dt);
            Game::setupGui();
        };


    Game::canvas.run(update, Game::controller);
    
    return 0;
}