#pragma once

#include "../System/ECS.h"
#include "../System/Input.h"
#include "../Transform.h"
#include "../Graphics/GraphicsComponents.h"
#include "../Physics/PhysicsComponents.h"
#include "../System/Utilities.h"
#include "../World/World.h"
#include "../World/Tile.h"

class Player : public Entity
{
public:
    Player() : Entity{} 
    {
        //AddComponent<ru::TransformComponent>();
        //AddComponent<ru::PlayerControllerComponent>();
        
    }

    ~Player()
    {

    }

    void Update(float dt)
    {
        Entity::Update();

        if (HasComponent<ru::PlayerControllerComponent>())
        {
            auto& a = GetComponent<ru::PlayerControllerComponent>();

            sf::Vector2f movedirection;

           /* if (a.GetKey("L-Mouse").isPressed)
            {
                
                sf::Vector2f mPos = world->window->mapPixelToCoords(sf::Mouse::getPosition());

                Get Map and move to tile
                ru::Tile* t = world->GetTileOnMouse(mPos);

                if(t)
                    GetComponent<ru::TransformComponent>().transform.pos = t->GetComponent<ru::TransformComponent>().transform.pos;
            }*/

            if (a.GetKey("Forward").isPressed)
            {
                movedirection.y -= speed * dt;
            }

            if (a.GetKey("Backward").isPressed)
            {
                movedirection.y += speed * dt;
            }

            if (a.GetKey("Left").isPressed)
            {
                movedirection.x -= speed * dt;
            }

            if (a.GetKey("Right").isPressed)
            {
                movedirection.x += speed * dt;
            }

            if (HasComponent<ru::TransformComponent>())
            {
                if (HasComponent<ru::PhysicsMovementComponent>())
                {
                    movedirection = ru::Normalize<float>(movedirection);
                    GetComponent<ru::PhysicsMovementComponent>().direction = movedirection;
                }
            }
        }
    }

public:
    float speed = 10.0f;


};