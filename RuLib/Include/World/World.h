#pragma once

#include <SFML/Graphics/Transform.hpp>

namespace ru
{
    class Map;
    class Tile;
    struct Room;
}

namespace sf
{
    class RenderWindow;
}

namespace ru
{
    class World
    {
    public:
        World();
        ~World();

        ru::Room* GetRoomOnMouse(sf::Vector2f mPos);
        ru::Tile* GetTileOnMouse(sf::Vector2f mPos);
        sf::Vector2f GetMousePosition();

    public:

        ru::Map* map;
        sf::RenderWindow* window;
    };
}
