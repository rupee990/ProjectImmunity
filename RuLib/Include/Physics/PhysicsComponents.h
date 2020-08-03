#pragma once
#include "../System/ECS.h"
#include "../Transform.h"
#include "../System/Input.h"

//All Sorts of Physics Components

enum PhysicsType
{
    STATIC,
    DYNAMIC
};

enum CollisionType
{
    RECTANGLE,
    CIRCLE,
    SHAPE
};

namespace ru
{
    class BasePhysComponent : public Component
    {
    public:
        PhysicsType phys_type;
        CollisionType col_type;

        bool awake = false;

        void Update() override
        {
            if (entity->HasComponent<ru::TransformComponent>())
            {
               pos = entity->GetComponent<ru::TransformComponent>().transform.pos;
            }
        }

        sf::Vector2f pos;
    };

    class CircleComponent : public BasePhysComponent
    {
    public:
        float radius;
    };

    class RectangleComponent : public BasePhysComponent
    {
    public:
        //RectangleComponent(sf::Vector2f size)
        //{
        //    rect.sizex = size.x;
        //    rect.sizey = size.y;
        //}

        void Update()
        {
            BasePhysComponent::Update();
            rect.pos = pos;
        }

        ru::RRect rect;
    };

    class LineComponent : public BasePhysComponent
    {
    public:
        sf::Vector2f a;
        sf::Vector2f b;

        float length;
        sf::Vector2f direction;
    };

    //
    /*
    * Physics Based Movement Component
    * A simplecontainer to that calculates movement
    */

    class PhysicsMovementComponent : public Component
    {
    public:
        void Update() override
        {
            if (entity->HasComponent<ru::TransformComponent>())
            {
                ru::Transform& eTransform = entity->GetComponent<ru::TransformComponent>().transform;

                    oldPos = eTransform.pos;

                    if (direction != sf::Vector2f())
                    {
                        if (oldDirection != direction)
                        {
                            ru::PlayerControllerComponent& pcontroller = entity->GetComponent<ru::PlayerControllerComponent>();

                            int keysPressed = 0;
                            for(auto a : pcontroller.keys)
                            {
                                if (a.second.isPressed == false)
                                    continue;

                                keysPressed++;
                            }

                            if (keysPressed >= 1)
                                oldDirection = direction;
                            else if (keysPressed >= 2)
                            {
                                direction *= 0.5f;
                                oldDirection = direction;
                            }

                        }

                        /*Calculate new Position based on velocity*/
                        sf::Vector2f nPos;
                        if (Velocity <= MaxVelocity)
                        {
                            Velocity = Velocity + (acceleration * (1 / 60.0f));
                        }


                        nPos = oldPos + (direction * Velocity);
                        entity->GetComponent<ru::TransformComponent>().transform.pos = nPos;
                    }
                    else if(Velocity > 0)
                    {
                        Velocity = Velocity - (decceleration * (1 / 60.0f));

                        sf::Vector2f nPos = oldPos + (oldDirection * Velocity);

                        entity->GetComponent<ru::TransformComponent>().transform.pos = nPos;
                    }
                    else if (Velocity < 0)
                    {
                        Velocity = 0;
                    }
            }
        }

        float MaxVelocity = 1.0f;

        float Velocity;
        float acceleration = 1.0f;
        float decceleration = 20.0f;
        float mass = 1.0f;
        
        sf::Vector2f direction;
        sf::Vector2f oldDirection;
        sf::Vector2f oldPos;
    };
}
