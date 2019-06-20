#pragma once

#include "ECS.h"
#include "SFML/System/Vector2.hpp"
#include "..\lib\glm\glm\glm.hpp"

namespace ru
{
    struct Transform
    {
        sf::Vector2f pos;
        float rot;
        sf::Vector2f scale;
    };


    struct Rect
    {
        sf::Vector2f pos;
        float sizex;
        float sizey;
    };

    class TransformComponent : public Component
    {

    public:
        sf::Vector2f pos;
        float rot;
        sf::Vector2f scale;
    };

    /*glm::vec2 GetDirection(glm::vec2 A, glm::vec2 B)
    {
        glm::vec2 direction;
        direction.x = (B.x - A.x);
        direction.y = (B.y - A.y);
    
        return glm::normalize(direction);
    }   */
}