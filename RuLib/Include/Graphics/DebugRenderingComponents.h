#pragma once

#include "../System/ECS.h"
#include "GraphicsComponents.h"
#include "../Transform.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "../World/World.h"
#include "../Physics/PhysicsComponents.h"

#define TileSizeX 32
#define TileSizeY 32


namespace ru
{
    class DebugBox : public Component
    {
    public:
        DebugBox()
        {


        }

        ~DebugBox()
        {

        }

        void Init() override
        {
            if (entity->HasComponent<ru::TransformComponent>())
            {
                rectangle.setPosition(entity->GetComponent<ru::TransformComponent>().transform.pos);
                rectangle.setFillColor(sf::Color::Transparent);
                rectangle.setSize(sf::Vector2f(TileSizeX, TileSizeY));
                rectangle.setOutlineColor(sf::Color::Green);
                rectangle.setOutlineThickness(1.0f);
            }
        }

        void Update() override
        {
            if (entity->HasComponent<ru::RectangleComponent>())
            {
                rectangle.setSize(sf::Vector2f(entity->GetComponent<ru::RectangleComponent>().rect.sizex, entity->GetComponent<ru::RectangleComponent>().rect.sizex));
                rectangle.setPosition(entity->GetComponent<ru::RectangleComponent>().rect.pos);
            }
        }

        void Draw() override
        {
            entity->world->window->draw(rectangle);
        }

        sf::RectangleShape rectangle;
    };
}