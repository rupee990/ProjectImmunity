#pragma once

#include "PhysicsComponents.h"
#include "Transform.h"

/*
* HandlesCollisions
*/

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    void Update();

    //Simple AABB Check
    bool RectCollisionCheck(const ru::RectangleComponent A, const ru::RectangleComponent B);
    bool CircleCollisionCheck(const ru::CircleComponent A, const ru::CircleComponent B);
    bool LineIntersectCheck(const ru::LineComponent A, const ru::LineComponent B);

    //Utilities
    float GetDistance(const glm::vec2 A, const glm::vec2 B);
    int Orientation(const glm::vec2 A, const glm::vec2 B, const glm::vec2 C);
    bool OnSegement(const glm::vec2 A, const glm::vec2 B, const glm::vec2 C);

};