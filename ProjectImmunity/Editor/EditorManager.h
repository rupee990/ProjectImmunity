#pragma once

#include "Tile.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"
#include "../Global.h"

#define GRID_SIZE_X 16
#define GRID_SIZE_Y 16

class Map;
class ResourceManager;
class Renderer;
class MapEditor;

/*
* Editor Manager Manages all the tools that are used, Updates them and handles the Imgui menus.
*/
class Editor
{
public:
    Editor(ResourceManager* rm_, Renderer* renderer_, sf::RenderWindow* window_);
    ~Editor();

    void Update(float dt);

    //Renders grid on screen
    void Render();

public:
    Map* map;
    ResourceManager* rm;
    sf::RenderWindow* window;
    Renderer* renderer;

    //Editors
    MapEditor* mapEditor;

    //Bools For window
    bool isMapEditorOpen = true;
};