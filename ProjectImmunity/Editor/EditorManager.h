#pragma once

#include "Tile.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"
#include "../Global.h"

#define GRID_SIZE_X 16
#define GRID_SIZE_Y 16


namespace ru
{
    class ResourceManager;
    class Renderer;
    class Map;
}
class MapEditor;
class Game;
class PhysicsManager;

/*
* Editor Manager Manages all the tools that are used, Updates them and handles the Imgui menus.
*/
class Editor
{
public:
    Editor(Game* sim, ru::ResourceManager* rm_, ru::Renderer* renderer_, sf::RenderWindow* window_, EntityManager* _eManager, PhysicsManager* _pManager);
    ~Editor();

    void Update(float dt);

    //Renders grid on screen
    void Render();

public:
    ru::Map* map;
    ru::ResourceManager* rm;
    sf::RenderWindow* window;
    ru::Renderer* renderer;
    PhysicsManager* pm;

    EntityManager* eManager;
    Game* game;

    //Editors
    MapEditor* mapEditor;

    //Bools For window
    bool isMapEditorOpen = true;
    bool hasFocusOnce = false;
};