#pragma once
#include <vector>
#include <string>

namespace ru
{
    class Map;
    class Room;
    class ResourceManager;
}
class Editor;

#define ButtonWidth 100
#define ButtonHeight 100

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
    BRUSH,
    ERASE,
    COLLIDER
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
    void NewRoom(unsigned int sizex_, unsigned int sizey_, float posx_, float posy_, std::string TileMap = "DebugTileMap");

    //Various PopUps
    void OpenTilemapPopup();
    void TilemapParametersPopup();

    //Refresh used Assets
    void RefreshAssets();
    

private:

    ru::Map*    map;
    Editor*     editor;
    EditorTabs  currentTab = TILEMAP;
    ToolStates  toolState = SELECT;

    sf::Texture* tilemap;
    std::string tileMapAssetId;
    sf::Sprite* tilemapSprite;

    ru::Room* selectedRoom;
    sf::Sprite* selectedTile;
    sf::Sprite* tilePreview;

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

    int layer = 0;

};