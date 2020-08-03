#pragma once

#include "SFML/Graphics.hpp"
#include "../Global.h"
#include "cereal/archives/json.hpp"
#include "Transform.h"
#include "../Core/GameComponents.h"

#include "System/ECS.h"

struct TextureResource;

#define TileSizeX 32.0f
#define TileSizeY 32.0f

class Tile : public Entity
{
public:
    Tile() {};

    /*Tile(sf::Texture* _tex, Renderer* _renderer)
    {
        this->AddComponent<ru::TransformComponent>();
        this->AddComponent<ru::SpriteComponent>(_tex, _renderer);
    }*/

   /* void Init(sf::Texture* _tex, Renderer* _renderer)
    {
        this->AddComponent<ru::TransformComponent>();
        this->AddComponent<ru::SpriteComponent>(_tex, _renderer);
    }*/

    //Tile()
    //{

    //}

    unsigned int id;
    sf::Vector2i coord;
};