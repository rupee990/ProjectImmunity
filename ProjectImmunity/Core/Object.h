#pragma once

#include "SFML/Graphics.hpp"

class Object
{
public:
    Object() {};
    ~Object() {};

    void Update() {};

public:
    int id;
    sf::Sprite sprite;
};