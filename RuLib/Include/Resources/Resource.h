#pragma once

#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "../Transform.h"

/*
* JSON ARCHIVE FOR SFML MATH
*/




namespace ru
{
    enum ResourceType
    {
        TEXTURE,
        MAP,
        TILE,
        OBJECT
    };

    namespace resource
    {
        struct rInterface
        {
            std::string name;

            unsigned int id;
            ru::ResourceType type;
        };

        struct Tile : rInterface
        {
            Tile() : rInterface{}
            {

            }

            sf::Vector2i coord;
            ru::Transform transform;
            sf::IntRect textureRect;

            template <class Archive>
            void save(Archive& archive) const
            {
                archive(CEREAL_NVP(coord.x), CEREAL_NVP(coord.y), CEREAL_NVP(transform), CEREAL_NVP(textureRect.width), CEREAL_NVP(textureRect.height), CEREAL_NVP(textureRect.top), CEREAL_NVP(textureRect.left));
            };

            template <class Archive>
            void load(Archive& archive)
            {
                archive(CEREAL_NVP(coord.x), CEREAL_NVP(coord.y), CEREAL_NVP(transform), CEREAL_NVP(textureRect.width), CEREAL_NVP(textureRect.height), CEREAL_NVP(textureRect.top), CEREAL_NVP(textureRect.left));
            };
        };

        struct Room : rInterface
        {
            ru::Transform transform;
            sf::Vector2i size;

            std::vector <Tile*> tiles;

            template<class Archive>
            void save(Archive& archive) const
            {
                archive(CEREAL_NVP(transform), CEREAL_NVP(size.x), CEREAL_NVP(size.y));
            }

            template<class Archive>
            void load(Archive& archive)
            {
                archive(CEREAL_NVP(transform), CEREAL_NVP(size.x), CEREAL_NVP(size.y));
            }
        };

        struct Map :  rInterface
        {
            std::string tilemapName;
            int numberOfRooms;

            std::vector <Room*> rooms;
            
            int version;

            template<class Archive>
            void save(Archive& archive) const
            {
                archive(CEREAL_NVP(name), CEREAL_NVP(tilemapName), CEREAL_NVP(numberOfRooms));
            };

            template<class Archive>
            void load(Archive& archive)
            {
                archive(CEREAL_NVP(name), CEREAL_NVP(tilemapName), CEREAL_NVP(numberOfRooms));
            };

        };

        struct GameObject : rInterface
        {

        };

        struct Texture : rInterface
        {
            Texture(sf::Texture& texture) : texture(texture)
            {

            }

            sf::Texture& texture;
        };
    }
}