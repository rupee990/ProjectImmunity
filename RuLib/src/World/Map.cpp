#include "World/Map.h"

ru::Map::Map(BaseSystems* _bs) : baseSystems(_bs)
{

}

ru::Map::~Map()
{

}

void ru::Map::AddRoom(sf::Vector2i size)
{
    static int roomId = 0;

    for (int i = 0; i < size.y; i++)
    {
        for (int j = 0; j < size.x; j++)
        {
            for (int i = 0; i < GroupsAmount; i++)
            {
                sf::Texture& tex = baseSystems->resourceManager->GetTexture("32x32Tilemap");
                ru::Tile* t = new ru::Tile(&tex);

                rooms[roomId]->tiles[(GroupType)(i)].push_back(t);
            }
        }
    }
}

void ru::Map::AddRoom(ru::Room* _room)
{
    rooms.push_back(_room);
}

//void Map::AddTile(ru::Tile* tile, int room_)
//{
//    if(tile != nullptr)
//        tiles[room_].push_back(tile);
//
//}