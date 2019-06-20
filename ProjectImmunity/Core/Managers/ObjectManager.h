#pragma once
#include <map>
#include "../Object.h"
#include "SFML/Graphics.hpp"


class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    void Update();

    void AddObject(sf::Vector2f pos, sf::Texture& tex);
    void AddObject(Object& object);

    Object* GetObject(std::string name) { return objects[name]; }
    Object* GetObject(int id) 
    { 
        for (auto& a : objects) 
        { 
            if (a.second->id == id) 
                return a.second; 
        }

        return nullptr;
    };

private:

    std::map<std::string, Object*> objects;
};