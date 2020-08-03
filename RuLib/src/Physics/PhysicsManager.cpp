#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponents.h"
#include "System/Utilities.h"
#include "Engine.h"

PhysicsManager::PhysicsManager(ru::Engine* _engine)
{
    m_engine = _engine;
}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update()
{
    if (BroadPhase())
    {
        NarrowPhase();
    }

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
    if (GetDistance(A.pos, B.pos) < A.radius + B.radius)
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

void PhysicsManager::Impulse(ru::PhysicsMovementComponent& body, float force, sf::Vector2f direction)
{
    //body.awake = true;

    //if (body.phys_type == RECTANGLE)
    //{
    //    ru::RectangleComponent& rect = static_cast<ru::RectangleComponent&>(body);
    //}
    
    body.direction = direction;
    body.Velocity = body.Velocity - force;

}


bool PhysicsManager::BroadPhase()
{

    NarrowChecks.clear();
    for (auto c : Colliders)
    {
        if (c->phys_type == STATIC)
            continue; 

        int current = NarrowChecks.size();

        if (c->entity->HasComponent<ru::RectangleComponent>())
        {
            ru::RectangleComponent* rect = static_cast<ru::RectangleComponent*>(c);

            if (rect->awake)
            {
                for (auto c2 : Colliders)
                {
                    ru::RectangleComponent* rect2 = static_cast<ru::RectangleComponent*>(c2);

                    if (rect == rect2)
                        continue;

                    if (GetDistance<float>(rect->pos, rect2->pos) <= 64)
                    {
                        NarrowChecks.push_back(rect2);
                    }
                }
            }

            if (current != NarrowChecks.size())
            {
                current = NarrowChecks.size();
                NarrowChecks.push_back(rect);
            }
        }


    }

    if (NarrowChecks.size() > 0)
        return true;
    
    return false;
}

void PhysicsManager::NarrowPhase()
{
    for (auto a : NarrowChecks)
    {
        if (NarrowChecks.size() >= 2)
        {
            for (int i = 0; i < NarrowChecks.size(); i++)
            {
                ru::RectangleComponent* baseA = static_cast<ru::RectangleComponent*>(a);
                ru::RectangleComponent* baseB = static_cast<ru::RectangleComponent*>(NarrowChecks[i]);

                if (baseA == baseB)
                    continue;

                if (baseA->phys_type != STATIC || baseB->phys_type != STATIC)
                {

                    if (ru::AABB<float>(baseA->rect.pos, baseB->rect.pos, sf::Vector2f(32.0f, 32.0f)))
                    {
                        if (NarrowChecks[i]->entity->HasComponent<ru::PhysicsMovementComponent>())
                        {
                            ru::PhysicsMovementComponent& tcomp = NarrowChecks[i]->entity->GetComponent<ru::PhysicsMovementComponent>();

                            static sf::Vector2f onCollisionDirection = tcomp.direction;
                            static float onCollisionVelocity = tcomp.Velocity;

                            tcomp.entity->GetComponent<ru::PhysicsMovementComponent>().Velocity = -onCollisionVelocity;

                            NarrowChecks[i]->entity->GetComponent<ru::DebugBox>().rectangle.setOutlineColor(sf::Color::Red);
                            //Impulse(tcomp.entity->GetComponent<ru::PhysicsMovementComponent>(), 5.0f, -tcomp.direction);
                        }
                        else
                        {
                            NarrowChecks[i]->entity->GetComponent<ru::DebugBox>().rectangle.setOutlineColor(sf::Color::Green);
                        }
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//Utilities
/////////////////////////////////////////////////////////////////////////////////////

template <typename T>
float PhysicsManager::GetDistance(const sf::Vector2<T> A, const sf::Vector2<T> B)
{
    return sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
}

template <typename T>
int PhysicsManager::Orientation(const sf::Vector2<T> A, const sf::Vector2<T> B, const sf::Vector2<T> C)
{
    float val = (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2;
}

template <typename T>
bool PhysicsManager::OnSegement(const sf::Vector2<T> A, const sf::Vector2<T> B, const sf::Vector2<T> C)
{
    if (B.x <= std::max(A.x, C.x) &&
        B.x >= std::min(A.x, C.x) &&
        B.y <= std::max(A.y, C.y) &&
        B.y >= std::min(A.y, C.y))
            return true;

    return false;
}