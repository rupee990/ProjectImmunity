#include "Map.h"
#include "../Editor/Tile.h"

#include "SFML/Graphics.hpp"

//////////////////////////////////////////

void Room::SetPos(float arr[2])
{
    position.x = arr[0];
    position.y = arr[1];

    for (auto& a : tiles)
    {
        a->sprite.setPosition(arr[0] + (a->coord.x * 16), arr[1] + (a->coord.y * 16));
    }
}


/////////////////////////////////////////

Map::Map()
{

}

Map::~Map()
{

}

void Map::AddTile(sf::Vector2f position_, sf::Vector2i size_, sf::Texture& texture_)
{
    Tile* tile = new Tile;

    sf::Sprite spr;
    spr.setTexture(texture_);
    tile->sprite = spr;

    tile->sprite.setPosition(position_);
    tile->id = tileIds++;

    rooms[tile->id]->tiles.push_back(tile);
}