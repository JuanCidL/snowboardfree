#pragma once
#include <nothofagus.h>

class Sign
{
public:
    Sign(glm::vec2 position, std::string text);

    const void update(float dt);
    const void reset();

private:
    const glm::vec2 position;
    Nothofagus::BellotaId bellotaId;
    Nothofagus::BellotaId textBellotaId;
    bool spawned;
};