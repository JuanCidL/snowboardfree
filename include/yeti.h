#include "entity.h"

namespace Entity
{

class Yeti: public AnimatedEntity
{

public:
    Yeti(glm::vec2 position);
    
    void update(float dt) override;
    void reset() override;
    void eat();

private:
    float stepTime;
    float stepDuration;
};

}