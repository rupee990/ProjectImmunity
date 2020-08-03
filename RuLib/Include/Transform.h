#pragma once

#include "System/ECS.h"
#include "SFML/System/Vector2.hpp"
#include "cereal/cereal.hpp"

namespace ru
{
    struct Transform
    {
        sf::Vector2f pos;
        float rot;
        sf::Vector2f scale;

        template<class Archive>
        void save(Archive& archive) const
        {
            archive(CEREAL_NVP(pos.x), CEREAL_NVP(pos.y), CEREAL_NVP(rot), CEREAL_NVP(scale.x), CEREAL_NVP(scale.y));
        };

        template<class Archive>
        void load(Archive& archive)
        {
            archive(CEREAL_NVP(pos.x), CEREAL_NVP(pos.y), CEREAL_NVP(rot), CEREAL_NVP(scale.x), CEREAL_NVP(scale.y));
        };

    };

    struct RRect
    {
        sf::Vector2f pos;
        float sizex;
        float sizey;
    };

    class TransformComponent : public Component
    {
    public:
        TransformComponent() 
        { 

        };

        void Init() override
        {
            transform.pos = sf::Vector2f(0.0f, 0.0f);
            transform.rot = 0.0f;
            transform.scale = sf::Vector2f(1.0f, 1.0f);
        }

        Transform transform;

        template<typename Archive>
        void save(Archive& archive) const
        {
            archive(transform);
        }

        template<typename Archive>
        void load(Archive& archive)
        {
            archive(transform);
        }

    };

    /*glm::vec2 GetDirection(glm::vec2 A, glm::vec2 B)
    {
        glm::vec2 direction;
        direction.x = (B.x - A.x);
        direction.y = (B.y - A.y);
    
        return glm::normalize(direction);
    }   */
}