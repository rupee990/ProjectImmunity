#pragma once

#include <map>
#include "Tile.h"
#include "../Transform.h"
#include "../Graphics/GraphicsComponents.h"

namespace ru
{
    struct Room : public Entity
    {
        Room() : Entity {}{};

        void Update()
        {
            Entity::Update();

            for (int i = 0; i < GroupsAmount; i++)
            {
                for (ru::Tile* t : tiles[(GroupType)(i)])
                {
                    sf::Vector2f nPos = t->GetComponent<ru::TransformComponent>().transform.pos;
                    nPos += transform.pos;

                    t->GetComponent<ru::TransformComponent>().transform.pos = nPos;
                }
            }
        }

        template<typename Archive>
        void save(Archive& archive)
        {
            archive(size.x, size.y);
            GetComponent<ru::TransformComponent>().save(archive);
        }

        template<typename Archive>
        void load(Archive& archive)
        {
            archive(GetComponent<ru::TransformComponent>(), size.x, size.y);
            GetComponent<ru::TransformComponent>().load(archive);
        }

        //ru::Map* parentMap;

        ru::Transform transform;
        sf::Vector2i size;

        std::map<GroupType, std::vector<ru::Tile*>> tiles;
    };
}