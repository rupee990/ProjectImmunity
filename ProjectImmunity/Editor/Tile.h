#pragma once

#include "SFML/Graphics.hpp"
#include "../Global.h"
#include "cereal/archives/json.hpp"

struct TextureResource;

struct Tile
{
    unsigned int id;
    sf::Vector2i coord;

    sf::Sprite sprite;
    TextureResource* texture = nullptr;
};