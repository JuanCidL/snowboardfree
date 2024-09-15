#pragma once
#include <unordered_map>
#include <string>

namespace Piano
{

class Key
{
public:
	static Key& getInstance();
	static const float getKey(std::string key);

private:
	Key();
	static Key* instance;
	static std::unordered_map<std::string, float> keys;
	static void init();
};

class Piano
{
public:
	Piano()
	{

	}
};

}

