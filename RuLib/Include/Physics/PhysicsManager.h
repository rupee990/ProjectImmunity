#pragma once

#include "PhysicsComponents.h"
#include "../Transform.h"

namespace ru
{
    class Engine;
}

/*
* HandlesCollisions
*/

class PhysicsManager
{
public:
    PhysicsManager(ru::Engine* _engine);
    ~PhysicsManager();

    void Update();

    //Simple AABB Check
    bool RectCollisionCheck(const ru::RectangleComponent A, const ru::RectangleComponent B);
    bool CircleCollisionCheck(const ru::CircleComponent A, const ru::CircleComponent B);
    bool LineIntersectCheck(const ru::LineComponent A, const ru::LineComponent B);

    //Forces
    void Impulse(ru::PhysicsMovementComponent& body, float force, sf::Vector2f direction);

    //Utilities
    template <typename T>
    float GetDistance(const sf::Vector2<T> A, const sf::Vector2<T> B);

    template <typename T>
    int Orientation(const sf::Vector2<T> A, const sf::Vector2<T> B, const sf::Vector2<T> C);

    template <typename T>
    bool OnSegement(const sf::Vector2<T> A, const sf::Vector2<T> B, const sf::Vector2<T> C);

    bool BroadPhase();
    void NarrowPhase();

    void Register(ru::BasePhysComponent* comp) { Colliders.push_back(comp); }

    void Deregister(ru::BasePhysComponent* comp)
    {
        for (std::vector<ru::BasePhysComponent*>::const_iterator iter = Colliders.begin(); iter != Colliders.end(); iter++)
        {
            if (*iter == comp)
                Colliders.erase(iter);
        } 
    }

private:
    std::vector<ru::BasePhysComponent*> Colliders;

    std::vector<ru::RectangleComponent*> NarrowChecks;

    ru::Engine* m_engine;

};