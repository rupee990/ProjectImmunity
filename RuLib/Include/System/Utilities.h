#pragma once

#include "../Transform.h"
#include "../Resources/ResourceManager.h"
#include "../Graphics/Renderer.h"

namespace ru
{
    /*/////////////////////////////////////////
    * //Normalize vector func
    //////////////////////////////////////////*/
    template<typename T>
    inline sf::Vector2<T> Normalize(sf::Vector2<T> source)
    {
        float length = sqrt((source.x * source.x) + (source.y * source.y));
        if (length != 0)
            return sf::Vector2<T>(source.x / length, source.y / length);
        else
            return source;
    }

    /*/////////////////////////////////////////
    * //AABB CHECKS
    //////////////////////////////////////////*/
    template<typename T>
    inline bool AABB(T AX, T AY, T BX, T BY, float size)
    {
        if (AX < BX &&
            AX > BX + size &&
            AY < BY &&
            AY > BY + size)
        {
            return true;
        }

        return false;
    }

    template<typename T>
    inline bool AABB(sf::Vector2<T> A, sf::Vector2<T> B, sf::Vector2<T> size)
    {
        if (A.x < B.x + size.x &&
            A.x + size.x > B.x &&
            A.y < B.y + size.y &&
            A.y + size.y > B.y)
        {
          return true;
        }

        return false;
    }

    template<typename T>
    inline bool AABB(sf::Vector2<T> A, sf::Vector2<T> sizeA , sf::Vector2<T> B, sf::Vector2<T> sizeB)
    {
        if (A.x < B.x + sizeB.x &&
            A.x + sizeA.x > B.x &&
            A.y < B.y + sizeB.y &&
            A.y + sizeA.y > B.y)
        {
            return true;
        }

        return false;
    }

    /*/////////////////////////////////////////
    * //Distance Checks
    //////////////////////////////////////////*/
    template <typename T>
    inline float GetDistance(T AX, T AY, T BX, T BY)
    {
        return sqrt(((BX - AX) * (BX - AX)) + ((BY - AY) * (BY - AY)));
    }

    template <typename T>
    inline float GetDistance(sf::Vector2<T> A, sf::Vector2<T> B)
    {
        return sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
    }

    template<typename T>
    inline bool DistCheck(T AX, T AY, T BX, T BY, float distance_)
    {
        float dist = GetDistance(AX, AY, BX, BY);

        if (dist < distance_)
        {
            return true;
        }

        return false;
    }

    template <typename T>
    inline bool DistCheck(sf::Vector2<T> A, sf::Vector2<T> B, float distance_)
    {
        float dist = GetDistance(A, B);

        if (dist < distance_)
        {
            return true;
        }

        return false;
    }

    /*/////////////////////////////////////////
    * //Linetrace
    //////////////////////////////////////////*/
    inline bool LineTrace(sf::Vector2f pos, sf::Vector2f dir)
    {
        return true;
    }

    template <typename T>
   inline sf::Vector2<T> GetDirection(sf::Vector2<T> A, sf::Vector2<T> B)
    {
        return ru::Normalize(sf::Vector2<T>(B.x - A.x, B.y - A.y));
    }
}


/*/////////////////////////////////////////
 * // Base System Class to be inherited by classes
//////////////////////////////////////////*/

class BaseSystems
{
public:
    BaseSystems(ru::ResourceManager* _rm, ru::Renderer* renderer) {};
    ~BaseSystems() {};

    ru::ResourceManager* resourceManager;
    ru::Renderer* renderer;
};