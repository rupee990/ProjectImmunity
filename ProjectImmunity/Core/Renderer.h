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

    unsigned int RegisterObject(sf::Drawable* object);
    void DeRegisterObject(unsigned int key);

    bool isRegistered(unsigned int key)
    { 
        if (registeredObjects.find(key) != registeredObjects.end()) 
            return true; 
        else 
            return false; 
    }

    void Render();
    static void Render(sf::Drawable& drawable);

    sf::RenderWindow& GetRenderTarget() { return *window; }

private:
    sf::RenderWindow* window;
    int renderIds = 0;

    std::map<unsigned int, sf::Drawable*> registeredObjects;

};