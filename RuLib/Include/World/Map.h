#pragma once

#include <vector>
#include <string>

#include "Room.h"
#include "../System/Utilities.h"
#include "cereal/cereal.hpp"
#include  "cereal/archives/json.hpp"

namespace ru
{
    class Map
    {
    public:
        Map(BaseSystems* _bs);
        ~Map();

        void ClearMap();
        void SetTileMap(std::string tilemapname) { tilemap = tilemapname; };
        std::string GetTileMap() { return tilemap; }


        void AddRoom(sf::Vector2i size);
        void AddRoom(ru::Room* _room);
        void AddTile(ru::Tile* t, int _room);
        void GetTile(int _room, int _t);

        std::vector<ru::Room*>& GetRooms()
        {
            return rooms;
        }

        ru::Room& GetRoom(int _id)
        {
            return *rooms[_id];
        }

        template<typename Archive>
        void save(Archive& archive) const
        {
            archive(rooms.size());
        }

        template<typename Archive>
        void load(Archive& archive)
        {
            archive(size);
        }


    private:
        int size;
        int version = 0x000010;

        std::string tilemap;
        std::vector<ru::Room*> rooms;

        BaseSystems* baseSystems;
    };
}