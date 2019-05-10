#pragma once

#include "SFML/Graphics.hpp"


namespace util
{

    /*/////////////////////////////////////////
    * //AABB CHECKS
    //////////////////////////////////////////*/
    template<typename T>
    bool AABB(T AX, T AY, T BX, T BY, float size)
    {
        if (AX > BX &&
            AX < BX + size &&
            AY > BY &&
            AY < BY + size)
        {
            return true;
        }

        return false;
    }

    bool AABB(sf::Vector2f A, sf::Vector2f B, sf::Vector2u size)
    {
        if (A.x > B.x &&
            A.x < B.x + size.x &&
            A.y > B.y &&
            A.y < B.y + size.y)
        {
            return true;
        }

        return false;
    }

    /*/////////////////////////////////////////
    * //Distance Checks
    //////////////////////////////////////////*/

    template <typename T>
    float GetDistance(T AX, T AY, T BX, T BY)
    {
        return sqrt(((BX - AX) * (BX - AX)) + ((BY - AY) * (BY - AY)));
    }

    float GetDistance(sf::Vector2f A, sf::Vector2f B)
    {
        return sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
    }

    template<typename T>
    bool DistCheck(T AX, T AY, T BX, T BY, float distance_)
    {
        float dist = GetDistance(AX, AY, BX, BY);

        if (dist < distance_)
        {
            return true;
        }

        return false;
    }

    bool DistCheck(sf::Vector2f A, sf::Vector2f B, float distance_)
    {
        float dist = GetDistance(A, B);

        if (dist < distance_)
        {
            return true;
        }

        return false;
    }


}