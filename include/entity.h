#pragma once
#include <nothofagus.h>

namespace Entity
{

extern glm::vec2& zeroVec2;

class BoundingBox
{
public:
    BoundingBox() :
        lbCorner{0, 0},
        rtCorner{0, 0}
    {}

    glm::vec2& leftBottomCorner()
    {
        return lbCorner;
    }
    
    const glm::vec2& leftBottomCorner() const
    {
        return lbCorner;
    }

    glm::vec2& rightTopCorner()
    {
        return rtCorner;
    }

    const glm::vec2& rightTopCorner() const
    {
        return rtCorner;
    }
    
private:
    glm::vec2 lbCorner, rtCorner;
};

class Entity
{
public:
    Entity();

    virtual void update(float dt);
    bool checkCollision(const Entity& other) const;
    virtual const glm::vec2& position() const;
    virtual const BoundingBox& boundingBox() const;
    virtual void reset();
    bool canCollide;

protected:
    BoundingBox _boundingBox;
private:
    glm::vec2 _position;
};

class StaticEntity : public Entity
{
public:
    StaticEntity(
        glm::ivec2 dimensions, glm::vec2 position,
        std::initializer_list<glm::vec4>colors,
        std::initializer_list<std::uint8_t> sprite);

    void update(float dt) override;
    void reset() override;
    const glm::vec2& position() const override;
    
protected:
    Nothofagus::BellotaId bellotaId;
};


class AnimatedEntity : public Entity
{
public:
    AnimatedEntity(
        glm::ivec2 dimensions, glm::vec2 position,
        std::initializer_list<glm::vec4> colors,
        std::initializer_list<std::initializer_list<std::uint8_t>> sprites);

    void update(float dt) override;
    const glm::vec2& position() const override;

protected:
    std::vector<Nothofagus::BellotaId> bellotaIds;
    Nothofagus::BellotaId currentBellotaId;
};


}