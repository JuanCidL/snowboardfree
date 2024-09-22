#pragma once
#include <unordered_map>
#include <string>
#include <rusty_audio.h>

namespace Piano
{

constexpr unsigned int sampleRate = 48000;
constexpr unsigned int channels = 2;

extern std::unordered_map<std::string, float> keys;

extern std::unordered_map<std::string, std::unique_ptr<RustyAudio::Player>> sounds;

void addSound(std::string key, std::unique_ptr<RustyAudio::Player> sound);


}

