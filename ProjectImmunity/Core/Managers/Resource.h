#pragma once

#include "../../Global.h"
#include "cereal/archives/json.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"

#include <string>
#include "SFML/Graphics.hpp"
#include "../Object.h"
#include "../Map.h"
#include "../../Editor/Tile.h"
#include "../../Utilities/SFMLserialize.h"

enum ResourceType
{
    TEXTURE,
    OBJECT,
    MAP,
};

struct TextureResource
{
    std::string name;
    unsigned int id;

    sf::Texture* texture;
};

struct ObjectResource
{
    std::string name;
    unsigned int id;

    ObjectResource* object;

    template<class Archive>
    void save(Archive& archive)
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(object->name));
    }

    template<class Archive>
    void load(Archive& archive)
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(object->name));
    }
};

/*
* Used to Save Tile information to to map
*/
struct TileResource
{
    Tile* tile;

    sf::IntRect texRect;
    sf::Vector2f position;

    template <class Archive>
    void save(Archive& archive) const
    {
        sf::serialize(archive, tile->coord);
        sf::serialize(archive, tile->sprite.getPosition());
        sf::serialize(archive, tile->sprite.getTextureRect());
    }

    template<class Archive>
    void load(Archive& archive)
    {
        sf::serialize(archive, tile->coord);
        sf::serialize(archive, position);
        sf::serialize(archive, texRect);
    }
};

struct RoomResource
{
    std::string tilemapName;

    Room* room;

    template<class Archive>
    void save(Archive& archive) const
    {
        archive(CEREAL_NVP(room->tilemapName));

        sf::serialize(archive, room->position);
        sf::serialize(archive, room->size);
    }   

    template<class Archive>
    void load(Archive& archive)
    {
        archive(CEREAL_NVP(room->tilemapName));

        sf::serialize(archive, room->position);
        sf::serialize(archive, room->size);
    }
};

struct MapResource
{
    std::string name;
    unsigned int id;
    unsigned int numberOfRooms;

    Map* map;

    template<class Archive>
    void save(Archive& archive) const
    {
        archive(CEREAL_NVP(name), CEREAL_NVP(numberOfRooms));
    }

    template<class Archive>
    void load(Archive& archive)
    {
        
        archive(CEREAL_NVP(name), CEREAL_NVP(numberOfRooms));
    }
};