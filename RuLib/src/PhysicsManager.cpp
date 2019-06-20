#include "../Include/PhysicsManager.h"

#include "glm/glm.hpp"
PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update()
{

}

bool PhysicsManager::RectCollisionCheck(const ru::RectangleComponent A, const ru::RectangleComponent B)
{
    if (A.rect.pos.x > B.rect.pos.x &&
        A.rect.pos.x < B.rect.pos.y + B.rect.sizex &&
        A.rect.pos.y > B.rect.pos.y &&
        A.rect.pos.y < B.rect.pos.y)
    {
        return true;
    }

    return false;
}

bool PhysicsManager::CircleCollisionCheck(const ru::CircleComponent A, const ru::CircleComponent B)
{
    if (GetDistance(A.position, B.position) < A.radius + B.radius)
    {
        return true;
    }

    return false;
}

bool PhysicsManager::LineIntersectCheck(const ru::LineComponent A, const ru::LineComponent B)
{
    int o1 = Orientation(A.a, A.b, B.a);
    int o2 = Orientation(A.a, A.b, B.b);
    int o3 = Orientation(B.a, B.b, A.a);
    int o4 = Orientation(B.a, B.b, A.b);

    // General cases
    if (o1 != o2 && o3 != o4) return true;


    //Exceptions
    if (o1 == 0 && OnSegement(A.a, B.a, A.b)) return true;

    if (o2 == 0 && OnSegement(A.a, B.b, A.b)) return true;

    if (o3 == 0 && OnSegement(B.a, A.a, B.b)) return true;

    if (o4 == 0 && OnSegement(B.a, A.b, B.b)) return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////////////////
//Utilities
/////////////////////////////////////////////////////////////////////////////////////

float PhysicsManager::GetDistance(const glm::vec2 A, const glm::vec2 B)
{
    return sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
}

int PhysicsManager::Orientation(const glm::vec2 A, const glm::vec2 B, const glm::vec2 C)
{
    float val = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2;
}

bool PhysicsManager::OnSegement(const glm::vec2 A, const glm::vec2 B, const glm::vec2 C)
{
    if (B.x <= std::max(A.x, C.x) &&
        B.x >= std::min(A.x, C.x) &&
        B.y <= std::max(A.y, C.y) &&
        B.y >= std::min(A.y, C.y))
            return true;

    return false;
}