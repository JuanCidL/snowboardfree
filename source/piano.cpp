#include "piano.h"

namespace Piano {

Key::Key() {};
Key* Key::instance = nullptr;

std::unordered_map<std::string, float> Key::keys;

Key& Key::getInstance()
{
	if (!instance)
	{
		instance = new Key();
		init();
	}
	return *instance;
}

const float Key::getKey(std::string key)
{
	return keys[key];
}

void Key::init()
{
	keys["A0"] = 27.500;
	keys["A#0"] = 29.1353;
	keys["B0"] = 30.8677;
	keys["C1"] = 32.7032;
	keys["C#1"] = 34.6479;
	keys["D1"] = 36.7081;
	keys["D#1"] = 38.8909;
}

}