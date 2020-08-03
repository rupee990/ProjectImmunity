#pragma once

#include "SFML/Graphics.hpp"
#include "Transform.h"


namespace util
{
    ///*/////////////////////////////////////////
    //* //AABB CHECKS
    ////////////////////////////////////////////*/
    //template<typename T>
    //bool AABB(T AX, T AY, T BX, T BY, float size)
    //{
    //    if (AX > BX &&
    //        AX < BX + size &&
    //        AY > BY &&
    //        AY < BY + size)
    //    {
    //        return true;
    //    }

    //    return false;
    //}

    //bool AABB(sf::Vector2f A, sf::Vector2f B, sf::Vector2u size)
    //{
    //    if (A.x > B.x &&
    //        A.x < B.x + size.x &&
    //        A.y > B.y &&
    //        A.y < B.y + size.y)
    //    {
    //        return true;
    //    }

    //    return false;
    //}

    ///*/////////////////////////////////////////
    //* //Distance Checks
    ////////////////////////////////////////////*/

    //template <typename T>
    //float GetDistance(T AX, T AY, T BX, T BY)
    //{
    //    return sqrt(((BX - AX) * (BX - AX)) + ((BY - AY) * (BY - AY)));
    //}

    //float GetDistance(sf::Vector2f A, sf::Vector2f B)
    //{
    //    return sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
    //}

    //template<typename T>
    //bool DistCheck(T AX, T AY, T BX, T BY, float distance_)
    //{
    //    float dist = GetDistance(AX, AY, BX, BY);

    //    if (dist < distance_)
    //    {
    //        return true;
    //    }

    //    return false;
    //}

    //bool DistCheck(sf::Vector2f A, sf::Vector2f B, float distance_)
    //{
    //    float dist = GetDistance(A, B);

    //    if (dist < distance_)
    //    {
    //        return true;
    //    }

    //    return false;
    //}

    ///*/////////////////////////////////////////
    //* //Raycasting
    ////////////////////////////////////////////*/

    //bool Raycast(sf::Vector2f pos, sf::Vector2f dir)
    //{
    //    return true;
    //}

    sf::Vector2f ToSfVec(glm::vec2 _vec)
    {
        return sf::Vector2f(_vec.x, _vec.y);
    }

    glm::vec2 ToGlmVec(sf::Vector2f _vec)
    {
        return glm::vec2(_vec.x, _vec.y);
    }
}
//
//namespace sf
//{
//    template<typename T>
//    class Vector2
//    {
//        glm::vec2 ToGlm()
//        {
//            return glm::vec2(this<T>.x, this<T>.y);
//        }
//    };
//}