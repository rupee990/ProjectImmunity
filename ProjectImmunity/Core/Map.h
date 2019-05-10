#pragma once

#include "../Global.h"
#include "Object.h"
#include <map>

#include "SFML/System.hpp"

struct Tile;

namespace sf
{
    class Texture;
}

struct Room
{
    std::string tilemapName;

    sf::Vector2f position;
    sf::Vector2u size;

    std::vector<Tile*> tiles;

    void SetPos(float arr[2]);
};

class Map : Object
{
public:
    Map();
    ~Map();

    void AddTile(sf::Vector2f position_, sf::Vector2i size_, sf::Texture& texture_);

    void Update();
    //void Render();

public:
    uint tileIds;

    sf::Vector2i size;
    sf::Vector2f position;

    std::map<uint, Room*> rooms;

};