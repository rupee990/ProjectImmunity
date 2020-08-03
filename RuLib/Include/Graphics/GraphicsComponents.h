#pragma once

#include "../System/ECS.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Renderer.h"
#include "../Transform.h"
#include "../World/World.h"

#define TileSizeX 32
#define TileSizeY 32

namespace ru
{
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent(sf::Texture& _texture, int _layer = 0, sf::IntRect _texRect = sf::IntRect(0,0,TileSizeX, TileSizeY))
        {
            sprite.setTexture(_texture);
            sprite.setTextureRect(_texRect);
            layer = _layer;
        };

        void Update()
        {
            if (entity->HasComponent<ru::TransformComponent>())
            {
                sprite.setPosition(entity->GetComponent<ru::TransformComponent>().transform.pos);
            }
        };

        void Draw()
        {
            entity->world->window->draw(sprite);
        }

        //Layer on which it gets Rendered (+1 front, -1 Back)
        int layer = 0;
        sf::Sprite sprite;
        
        int renderID;
    };
}