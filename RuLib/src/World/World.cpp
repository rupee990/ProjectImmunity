#include "World/World.h"
#include "System/Utilities.h"
#include "World/Map.h"
#include "World/Tile.h"
#include "SFML/Graphics/Transform.hpp"

ru::World::World()
{

}

ru::World::~World()
{

}

ru::Room* ru::World::GetRoomOnMouse(sf::Vector2f mPos)
{
    for (ru::Room* r : map->GetRooms())
    {
        sf::Vector2f roomCenter;

        roomCenter.x = r->transform.pos.x + (r->size.x * 0.5f);
        roomCenter.y = r->transform.pos.y + (r->size.y * 0.5f);

        if (ru::AABB(mPos, r->transform.pos, sf::Vector2f(r->size.x * TileSizeX, r->size.y * TileSizeY)))
        {
            return r;
        }
    }

    return nullptr;
}

ru::Tile* ru::World::GetTileOnMouse(sf::Vector2f mPos)
{
    ru::Room* room = GetRoomOnMouse(mPos);
    if (room)
    {
        for (int i = 0; i < GroupsAmount; i++)
        {
            for (ru::Tile* t : room->tiles[(GroupType)(i)])
            {
                sf::Vector2f tilePos = t->GetComponent<ru::TransformComponent>().transform.pos;

                if (ru::AABB(mPos, tilePos, sf::Vector2f(TileSizeX, TileSizeY)))
                {
                    return t;
                }
            }
        }
    }

    return nullptr;
}

sf::Vector2f ru::World::GetMousePosition()
{


    return sf::Vector2f();
}
