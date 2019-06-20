#include "MapEditor.h"

#include "EditorManager.h"
#include "../Core/Map.h"
#include "../Core/Managers/Resource.h"
#include "../Core/Managers/ResourceManager.h"
#include "../Core/Renderer.h"
#include "Utilities.h"
#include "Tile.h"
#include "../Core/Camera.h"

#include <iostream>
#include <string>

#define TileSizeX 32.0f
#define TileSizeY 32.0f

MapEditor::MapEditor(Editor* editor_)
{
    editor = editor_;

    int size = editor->rm->GetSizeByType(TEXTURE);

    //Get All Names for texture Items
    for (int i = 0; i < size; i++)
    {
        TextureResource* tex = editor->rm->GetTexture(i);
        if (tex)
        {
            textures_items.push_back(tex->name.c_str());
        }
    }

    //Get all names for map items
    size = editor->rm->GetSizeByType(MAP);

    for (int i = 0; i < size; i++)
    {
        map_items.push_back(editor->rm->GetMap(i)->name.c_str());
    }
}

MapEditor::~MapEditor()
{

}

void MapEditor::Update(float dt)
{
    if (toolState == SELECT)
    {
        if (ImGui::IsMouseClicked(0) && !ImGui::IsMouseHoveringAnyWindow() && map)
        {
            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition());
            for (auto& a : map->rooms)
            {
                sf::Vector2f roomCenter = a.second->position + sf::Vector2f((a.second->size.x * TileSizeX)* 0.5f, (a.second->size.y * TileSizeY) * 0.5f);

                //Check what room we are hovering
                if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(a.second->position, roomCenter)))
                {
                    //Select Room
                    selectedRoom = a.second;

                    roomPos[0] = selectedRoom->position.x;
                    roomPos[1] = selectedRoom->position.y;
                }
            }
        }
    }

    if (toolState == BRUSH)
    {
        if (ImGui::IsMouseClicked(0, true) && !ImGui::IsMouseHoveringAnyWindow() && map)
        {
            //glm::vec2 mpos = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition());

            for (auto& a : map->rooms)
            {
                sf::Vector2f roomCenter = a.second->position + sf::Vector2f((a.second->size.x * TileSizeX)* 0.5f, (a.second->size.y * TileSizeY) * 0.5f);

                //Check what room we are hovering
                if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(sf::Vector2f(a.second->position.x, a.second->position.y), roomCenter)))
                {
                    //Perform AABB
                    if (ru::AABB(mpos, a.second->position, sf::Vector2f(a.second->size.x * TileSizeX, a.second->size.y * TileSizeY)))
                    {
                        int x = (mpos.x - a.second->position.x) / TileSizeX;
                        int y = (mpos.y - a.second->position.y) / TileSizeY;

                        //Change the tile at location
                        a.second->tiles[x + a.second->size.x * y]->sprite.setTextureRect(selectedTile->getTextureRect());
                    }
                }
            }
        }

        if (selectedTile)
        {
            sf::Vector2f pos = editor->window->mapPixelToCoords(sf::Mouse::getPosition());

            int x = (int)((pos.x / TileSizeX) - 1) * TileSizeX;
            int y = (int)((pos.y / TileSizeY) - 2) * TileSizeY;

            tilePreview->setPosition(sf::Vector2f(x, y));
        }
    }
}

void MapEditor::UpdateEditorUI(float dt)
{
    ImGui::SetNextWindowPos(ImVec2(0, 20));
    ImGui::SetNextWindowSize(ImVec2(120, 980));
    ImGui::Begin("ToolBar");

    //Select Tool
    if (ImGui::Button("Select", ImVec2(ButtonWidth, ButtonHeight)))
    {
        toolState = SELECT;
    }
    //New Room Button
    if (ImGui::Button("Room", ImVec2(ButtonWidth, ButtonHeight)))
    {
        ImGui::OpenPopup("New Room");
    }

    //New Room Popup
    ImGui::SetNextWindowSize(ImVec2(300, 230));
    if (ImGui::BeginPopupModal("New Room"))
    {
        static int size[2];
        static float position[2];
        static const char* preview;
        static sf::Texture* tilemapTexturePreview;

        ImGui::InputFloat2("Position", position);
        ImGui::InputInt2("Size", size);

        if (ImGui::BeginCombo("Textures", preview))
        {
            for (int n = 0; n < textures_items.size(); n++)
            {
                bool is_selected = (preview == textures_items[n]);

                if (ImGui::Selectable(textures_items[n], is_selected))
                {
                    preview = textures_items[n];

                    tilemapTexturePreview = new sf::Texture;
                    tilemapTexturePreview = editor->rm->GetTexture(textures_items[n])->texture;
                }

                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (tilemapTexturePreview)
        {
            sf::Sprite* tilemapPreview = new sf::Sprite(*tilemapTexturePreview);
            ImGui::Image(*tilemapPreview);
        }

        if (ImGui::Button("Create"))
        {
            NewRoom(size[0], size[1], position[0], position[1], std::string(preview));
            tilemap = tilemapTexturePreview;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    //Brush Tool
    if (ImGui::Button("Brush", ImVec2(ButtonWidth, ButtonHeight)))
    {
        toolState = BRUSH;
    }
    //New Trigger Area
    if (ImGui::Button("Trigger Area", ImVec2(ButtonWidth, ButtonHeight)))
    {

    }

    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(1560, 20));
    ImGui::SetNextWindowSize(ImVec2(350, 950));
    ImGui::Begin("Editor", &editor->isMapEditorOpen);

    const char* editors[] = { "Map Editor", "Object Viewer", "Generation" };
    static int ctab = (int)currentTab;
    ImGui::Combo("Tab", &ctab, editors, IM_ARRAYSIZE(editors));
    currentTab = static_cast<EditorTabs>(ctab);

    ImGui::Separator();

    if (currentTab == TILEMAP)
    {
        ImGui::Text("Selected Room");

        //ImGui::InputInt2(": Position", roomPos, 16);
        ImGui::InputFloat(": X", &roomPos[0], TileSizeX, TileSizeX);
        ImGui::InputFloat(": Y", &roomPos[1], TileSizeX, TileSizeX);

        if (selectedRoom)
        {
            selectedRoom->SetPos(roomPos);
        }

        if (ImGui::Button("Delete"))
        {
            //Delete tiles from room
            for (int i = 0; i < selectedRoom->tiles.size(); i++)
            {
                editor->renderer->DeRegisterObject(i);
            }

            for (auto& a : map->rooms)
            {
                if (a.second == selectedRoom)
                {
                    delete(a.second);
                    map->rooms.erase(a.first);
                    break;
                }
            }
                //Deregister tiles from renderer

            //Delete room from map
        }

        ImGui::Separator();

        //Tile set viewer
        if (ImGui::Button("Load Tilemap"))
        {
            //Open Tilemap Selector
            ImGui::OpenPopup("TextureSelector");
        }
        if (ImGui::BeginPopupModal("TextureSelector"))
        {
            static int currentIndex = 0;
            static const char* preview;
            static sf::Texture* tilemapTexturePreview;

            if (ImGui::BeginCombo("Textures", preview))
            {
                for (int n = 0; n < textures_items.size(); n++)
                {
                    bool is_selected = (preview == textures_items[n]);

                    if (ImGui::Selectable(textures_items[n], is_selected))
                    {
                        preview = textures_items[n];

                        tilemapTexturePreview = new sf::Texture;
                        tileMapAssetId = textures_items[n];
                        tilemapTexturePreview = editor->rm->GetTexture(textures_items[n])->texture;
                        
                    }

                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            //ImGui::Combo("Textures_", &currentIndex, items, IM_ARRAYSIZE(items))

            //Tilemap Preview
            if (tilemapTexturePreview)
            {
                sf::Sprite* tilemapPreview = new sf::Sprite(*tilemapTexturePreview);
                ImGui::Image(*tilemapPreview);
            }

            ImGui::SetCursorPos(ImVec2(20, 200));
            if (ImGui::Button("Load"))
            {
                tilemap = tilemapTexturePreview;
                ImGui::CloseCurrentPopup();

            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        //tileMap Parameters
        if (ImGui::Button("Tilemap Parameters"))
        {
            ImGui::OpenPopup("TilemapParameters");
        }
        //Tilemap parameters popup, lets the user set properties for everytile (Walkable, wall, etc)

        //Loading Tilemap Popup
        ImGui::SetNextWindowSize(ImVec2(250, 230));


        static int uniformscale = 2.0f;
        ImGui::InputInt("Preview scale", &uniformscale);
        ImGui::Text("Selected TileMap");

        //Tilemap view in tab
        if (tilemap)
        {
            sf::Sprite* tspr = new sf::Sprite(*tilemap);
            
            sf::Vector2f tilemapPos = ImGui::GetCursorPos();
            tspr->setScale(sf::Vector2f(uniformscale, uniformscale));

            ImGui::Image(*tspr, sf::Color::White, sf::Color::White);

            ImGui::Text("selected Tile preview");
            //if we are hovering a window and a mouse button is pressed
            if (ImGui::IsMouseClicked(0) && ImGui::IsMouseHoveringAnyWindow())
            {
                sf::Vector2f mousePos = ImGui::GetMousePos();
                sf::Vector2f windowPos = ImGui::GetWindowPos();
                sf::Vector2u size = tspr->getTexture()->getSize();

                //if mouse is over tilemap preview
                if (ImGui::IsMouseHoveringRect(tilemapPos + windowPos, sf::Vector2f((tilemapPos.x + (size.x * uniformscale)) + windowPos.x,
                                                                                    (tilemapPos.y + (size.y * uniformscale)) + windowPos.y)))
                {
                    int x = (mousePos.x - (tilemapPos.x + windowPos.x)) / (TileSizeX * uniformscale);
                    int y = (mousePos.y - (tilemapPos.y + windowPos.y)) / (TileSizeY * uniformscale);

                    if (!selectedTile)
                    {
                        selectedTile = new sf::Sprite(*tspr);
                        selectedTile->scale(sf::Vector2f(2.0f, 2.0f));
                        
                        if (!tilePreview)
                        {
                            tilePreview = new sf::Sprite(*tspr);
                            tilePreview->scale(sf::Vector2f(0.5f, 0.5f));
                        }
                        static int key;
                        
                        if(!editor->renderer->isRegistered(key))
                            key = editor->renderer->RegisterObject(tilePreview);
                    }

                    tilePreview->setTextureRect(sf::IntRect(x * TileSizeX, y * TileSizeY, TileSizeX, TileSizeY));
                    selectedTile->setTextureRect(sf::IntRect(x * TileSizeX, y * TileSizeY, TileSizeX, TileSizeY));

                }
            }

            if (selectedTile)
            {
                ImGui::Image(*selectedTile);
            }
        }

        //Open Map
        if (ImGui::Button("Open Map"))
        {
            ImGui::OpenPopup("OpenMap");
        }

        if (ImGui::BeginPopupModal("OpenMap"))
        {
            static const char* preview;
            if (ImGui::BeginCombo(": Maps", preview))
            {

                for (int n = 0; n < map_items.size(); n++)
                {
                    bool is_selected = (preview == map_items[n]);

                    if (ImGui::Selectable(map_items[n], is_selected))
                    {
                        preview = map_items[n];
                    }

                    if (is_selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }

            //Clears current map and opens map.
            if (ImGui::Button("Load"))
            {

                //@TODO: Clear Map

                /*std::string s = 
                int a = std::stoi(s);*/
                map = editor->rm->GetMap(preview)->map;

                //Add Entire map to rendering
                for (auto& r : map->rooms)
                {
                    for (auto& t : r.second->tiles)
                    {
                        //Get texture
                        t->texture = new TextureResource;
                        t->texture->texture = new sf::Texture();
                        t->texture->texture = editor->rm->GetTexture(r.second->tilemapName)->texture;
                        t->sprite.setTexture(*t->texture->texture);

                        editor->renderer->RegisterObject(&t->sprite);
                    }
                }

                ImGui::CloseCurrentPopup();
            }

            //Import takes all the rooms within the map and moves them into the currently open map
            if (ImGui::Button("Import"))
            {
                for (auto& r : map->rooms)
                {
                    for (auto& t : r.second->tiles)
                    {
                        //Get texture
                        t->texture = new TextureResource;
                        t->texture->texture = new sf::Texture();
                        t->texture->texture = editor->rm->GetTexture(r.second->tilemapName)->texture;
                        t->sprite.setTexture(*t->texture->texture);

                        editor->renderer->RegisterObject(&t->sprite);
                    }
                }

                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        //Map Saving
        ImGui::SetCursorPos(ImVec2(0, 900));
        ImGui::Separator();
        static char buffer[32];
        ImGui::InputText("Filename", buffer, 32);

        if (ImGui::Button("Save Map"))
        {
            
            editor->rm->SaveAsset(map, buffer);
        }

    
    }
    else if (currentTab == OBJVIEWER)
    {
        //Object Viewer

        //Object placement
    }
    else if (currentTab == GENERATION)
    {

    }

    ImGui::End();

    
}

void MapEditor::Render()
{
    
}

void MapEditor::NewMap()
{
    if (map != nullptr)
        delete(map);

    map = new Map();
}

void MapEditor::NewRoom(unsigned int sizex_, unsigned int sizey_, float posx_, float posy_, std::string TileMap)
{
    if (!map)
    {
        std::cout << "[ERROR]No Map instance found, creating a new map." << std::endl;
        NewMap();
    }

    static int mapid = 0;

    //make sure that spot on map is empty
    while (map->rooms[mapid])
    {
        mapid++;
    }

    Room* room = new Room;
    room->tilemapName = TileMap;
    room->position = sf::Vector2f(posx_, posy_);
    room->size = sf::Vector2u(sizex_, sizey_);

    for (int i = 0; i < sizey_; i++)
    {
        for (int j = 0; j < sizex_; j++)
        {
            
            Tile* tile = new Tile;
            //tile->id = i + j * sizex_;

            //Set Up base texture and sprite
            tile->texture = editor->rm->GetTexture(TileMap);
            tile->sprite = sf::Sprite(*tile->texture->texture);
            tile->coord = sf::Vector2i(j, i);
            tile->sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TileSizeX, TileSizeY)));

            tile->sprite.setPosition(sf::Vector2f(  (j * tile->sprite.getTextureRect().width) + posx_, 
                                                    (i * tile->sprite.getTextureRect().height) + posy_));
            room->tiles.push_back(tile);

            tile->id = editor->renderer->RegisterObject(&tile->sprite);
        }
    }

    map->rooms[mapid] = room;
    mapid++;
}

void MapEditor::RefreshAssets()
{
    if (tileMapAssetId != "")
    {
        tilemap = editor->rm->GetTexture(tileMapAssetId)->texture;

        if (!map)
            return;

        for (auto& a : map->rooms)
        {
            for (auto& t : a.second->tiles)
            {
                t->sprite.setTexture(*tilemap);
            }
        }
    }
};