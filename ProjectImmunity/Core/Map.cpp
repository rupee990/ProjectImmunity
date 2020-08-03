#include "Map.h"
#include "../Editor/Tile.h"
#include "GameComponents.h"
#include "SFML/Graphics.hpp"
#include "Graphics/GraphicsComponents.h"

#include "Renderer.h"

//////////////////////////////////////////

void Room::SetPos(float arr[2])
{
    position.x = arr[0];
    position.y = arr[1];

    for (auto& a : tiles)
    {
        a->GetComponent<ru::TransformComponent>().transform.pos = sf::Vector2f(arr[0] + (a->coord.x * TileSizeX), arr[1] + (a->coord.y * TileSizeY));
    }
}


/////////////////////////////////////////

Map::Map(Renderer* renderer_) : renderer(renderer_)
{

}

Map::~Map()
{

}

void Map::AddTile(sf::Vector2f position_, sf::Vector2i size_, sf::Texture& texture_)
{
    Tile* tile = new Tile();

    sf::Sprite spr;
    spr.setTexture(texture_);
    tile->GetComponent<ru::SpriteComponent>().sprite = spr;

    tile->GetComponent<ru::TransformComponent>().transform.pos = position_;
    tile->id = tileIds++;

    rooms[tile->id]->tiles.push_back(tile);
}