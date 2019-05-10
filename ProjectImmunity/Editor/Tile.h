#pragma once

#include "SFML/Graphics.hpp"
#include "../Global.h"
#include "cereal/archives/json.hpp"

struct TextureResource;

struct Tile
{
    uint id;
    sf::Vector2i coord;

    sf::Sprite sprite;
    TextureResource* texture = nullptr;
};