#pragma once
#include "../Global.h"

#include <map>

#include "SFML/Graphics.hpp"
/*
*   Renderer keeps track of objects registered for render
*/
class Renderer
{
public:
    Renderer(sf::RenderWindow* window_);
    ~Renderer();

    uint RegisterObject(sf::Drawable* object);
    void DeRegisterObject(uint key);

    void Render();

private:
    sf::RenderWindow* window;
    int renderIds = 0;

    std::map<uint, sf::Drawable*> registeredObjects;

};