#pragma once

#include "../Global.h"
#include <vector>

class Map;
class ResourceManager;
class Editor;

#define ButtonWidth 100
#define ButtonHeight 22

enum EditorTabs
{
    TILEMAP = 0,
    OBJVIEWER,
    GENERATION
};

enum ToolStates
{
    SELECT,
    ROOM,
    BRUSH
};

namespace sf
{
    class Texture;
    class Sprite;
}

struct Room;

class MapEditor
{
public:
    MapEditor(Editor* editorManager_);
    ~MapEditor();

    void UpdateEditorUI(float dt);
    void Update(float dt);
    void Render();

    void NewMap(); //Initialize Map map and default map values
    void NewRoom(uint sizex_, uint sizey_, float posx_, float posy_, std::string TileMap = "DebugTileMap");

private:

    Map*        map;
    Editor*     editor;
    EditorTabs  currentTab = TILEMAP;
    ToolStates  toolState = SELECT;

    sf::Texture* tilemap;
    sf::Sprite* tilemapSprite;

    Room* selectedRoom;
    sf::Sprite* selectedTile;

    //Room Selection
    float roomPos[2] = { 0,0 };

    //Variables for Texture Selector Popup
    bool        isTextureSelectorOpen;
    const char* textureName;
    int*        texture_id;
    std::vector<const char*> textures_items;

    //Variables for New Map popup
    bool        isNewMapOpen;
    std::vector<const char*> map_items;



};