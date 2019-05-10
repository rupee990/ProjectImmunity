#pragma once

#include "SFML/Graphics.hpp"

class Object
{
public:
    Object() {};
    ~Object() {};

    static void Update();

protected:
    sf::Transform* transform;

};