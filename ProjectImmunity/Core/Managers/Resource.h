#pragma once

#include "../../Global.h"
#include "cereal/archives/json.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"

#include <string>
#include "../Object.h"
#include "../Map.h"
#include "../../Editor/Tile.h"
#include "../../Utilities/SFMLserialize.h"

#include "ECS.h"
#include "../GameComponents.h"
#include "Transform.h"

enum ResourceType
{
    TEXTURE,
    OBJECT,
    MAP,
};

struct TextureResource
{
    std::string name;
    std::string filepath;
    unsigned int id;

    sf::Texture* texture;
};

struct ObjectResource
{
    std::string name;
    unsigned int id;

    /*TODO: add general object data such as components and the information attached to the components*/

    //ObjectResource* object;

    template<class Archive>
    void save(Archive& archive)
    {
        archive(CEREAL_NVP(name));
    }

    template<class Archive>
    void load(Archive& archive)
    {
        archive(CEREAL_NVP(name));
    }
};

/*
* Used to Save Tile information to to map
*/
struct TileResource
{
   //Tile* tile ;

    sf::Vector2i coord;
    sf::IntRect texRect;
    sf::Vector2f position;

    template <class Archive>
    void save(Archive& archive) const
    {
        sf::serialize(archive, coord);
        sf::serialize(archive, position);
        sf::serialize(archive, texRect);
    }

    template<class Archive>
    void load(Archive& archive)
    {
        sf::serialize(archive, coord);
        sf::serialize(archive, position);
        sf::serialize(archive, texRect);
    }
};

struct RoomResource
{
    std::string tilemapName;

    sf::Vector2f position;
    sf::Vector2i size;

    std::vector<TileResource*> tiles;

    template<class Archive>
    void save(Archive& archive) const
    {
        archive(CEREAL_NVP(tilemapName));

        sf::serialize(archive, position);
        sf::serialize(archive, size);
    }   

    template<class Archive>
    void load(Archive& archive)
    {
        archive(CEREAL_NVP(tilemapName));

        sf::serialize(archive, position);
        sf::serialize(archive, size);
    }
};

struct MapResource
{
    std::string name;
    unsigned int id;
    unsigned int numberOfRooms;

    std::vector<RoomResource*> rooms;

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