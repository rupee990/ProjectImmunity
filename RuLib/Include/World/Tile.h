#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "../System/ECS.h"
#include "../Graphics/GraphicsComponents.h"

namespace ru
{
    class Tile : public Entity
    {
    public:
        Tile(sf::Texture* _tex) : Entity {} 
        {

            AddComponent<ru::TransformComponent>();
            AddComponent<ru::SpriteComponent>(*_tex);
        };

        ~Tile() {};

        template<typename Archive>
        void save(Archive& archive)
        {
            archive(GetComponent<ru::TransformComponent>(), coords.x, coords.y, size.x, size.y);
        }

        template<typename Archive>
        void load(Archive& archive)
        {
            archive(GetComponent<ru::TransformComponent>(), coords.x, coords.y, size.x, size.y);
        }

    public:
        //ru::Room* roomPointer;

        sf::Vector2u coords;
        sf::Vector2u size;

        /*sf::Texture* texture;
        sf::Sprite sprite;*/
    };
}