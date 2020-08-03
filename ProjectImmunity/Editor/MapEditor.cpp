#include "MapEditor.h"

#include "EditorManager.h"

#include "../Core/Game.h"
//#include "../Core/Managers/Resource.h"
//#include "../Core/Renderer.h"
//#include "Utilities.h"
//#include "Tile.h"

#include "../Core/Camera.h"
#include "../Core/GameComponents.h"

#include <iostream>
#include <string>

#include "SFML/Graphics/Sprite.hpp"

#include "World/Map.h"
#include "World/Room.h"
#include "World/Tile.h"
#include "System/Utilities.h"
#include "Graphics/GraphicsComponents.h"
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Physics/PhysicsComponents.h"
#include "Graphics/DebugRenderingComponents.h"
#include "Physics/PhysicsManager.h"
#include "World/World.h"
#include "System/ECS.h"
#include "Graphics/DebugRenderingComponents.h"


MapEditor::MapEditor(Editor* editor_)
{
    editor = editor_;

    std::vector<std::string> names = editor->rm->GetResourceNames(ru::ResourceType::TEXTURE);

    for (int i = 0; i < names.size(); i++)
    {       
        std::string* str = new std::string(names[i]);
        textures_items.push_back(str->c_str());
    }

    //for (int i = 0; i < size; i++)
    //{
    //    ru::resource::Texture* tex = editor->rm->GetTextureResource(i);
    //    if (tex)
    //    {
    //        textures_items.push_back(tex->name.c_str());
    //    }
    //}

    //Get all names for map items
    names = editor->rm->GetResourceNames(ru::ResourceType::MAP);

    for (int i = 0; i < names.size(); i++)
    {
        std::string* str = new std::string(names[i]);
        map_items.push_back(str->c_str());
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
            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window));
            for (ru::Room* a : map->GetRooms())
            {
                sf::Vector2f roomCenter = a->transform.pos + sf::Vector2f((a->size.x * TileSizeX)* 0.5f, (a->size.y * TileSizeY) * 0.5f);

                //Check what room we are hovering
                if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(a->transform.pos, roomCenter)))
                {
                    //Select Room
                    selectedRoom = a;

                    roomPos[0] = selectedRoom->transform.pos.x;
                    roomPos[1] = selectedRoom->transform.pos.y;
                }
            }
        }
    }

    if (toolState == BRUSH)
    {
        if (ImGui::IsMouseClicked(0, true) && !ImGui::IsMouseHoveringAnyWindow() && map && selectedTile != nullptr)
        {
            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window));

            for (auto& a : map->GetRooms())
            {
                sf::Vector2f roomCenter = a->transform.pos + sf::Vector2f((a->size.x * TileSizeX)* 0.5f, (a->size.y * TileSizeY) * 0.5f);

                //Check what room we are hovering
                if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(sf::Vector2f(a->transform.pos.x, a->transform.pos.y), roomCenter)))
                {
                    //Perform AABB
                    if (ru::AABB(mpos, a->transform.pos, sf::Vector2f(a->size.x * TileSizeX, a->size.y * TileSizeY)))
                    {
                        int x = (mpos.x - a->transform.pos.x) / TileSizeX;
                        int y = (mpos.y - a->transform.pos.y) / TileSizeY;

                        /*if (!editor->renderer->isRegistered(a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>()))
                        {
                            editor->renderer->Register(a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>());
                        }*/

                        //Change the tile at location
                        a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>().sprite.setTextureRect(selectedTile->getTextureRect());
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

    if (toolState == ERASE)
    {
        if (ImGui::IsMouseClicked(0, true) && !ImGui::IsMouseHoveringAnyWindow() && map)
        {
            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window));

            for (auto& a : map->GetRooms())
            {
                sf::Vector2f roomCenter = a->transform.pos + sf::Vector2f((a->size.x * TileSizeX)* 0.5f, (a->size.y * TileSizeY) * 0.5f);

                int x = (mpos.x - a->transform.pos.x) / TileSizeX;
                int y = (mpos.y - a->transform.pos.y) / TileSizeY;

                if (a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>().renderID != -1)
                {
                    //Check what room we are hovering
                    if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(sf::Vector2f(a->transform.pos.x, a->transform.pos.y), roomCenter)))
                    {
                         //Perform AABB
                         if (ru::AABB(mpos, a->transform.pos, sf::Vector2f(a->size.x * TileSizeX, a->size.y * TileSizeY)))
                         {
                                 //Change the tile at location
                                 editor->renderer->Deregister(a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>());
                                 a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::SpriteComponent>().renderID = -1;
                         }
                    }
                }
            }
        }
    }

    if (toolState == COLLIDER)
    {
        if (ImGui::IsMouseClicked(0, false) && !ImGui::IsMouseHoveringAnyWindow() && map)
        {
            sf::Vector2f mpos = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window));

            for (auto& a : map->GetRooms())
            {
                sf::Vector2f roomCenter = a->transform.pos + sf::Vector2f((a->size.x * TileSizeX)* 0.5f, (a->size.y * TileSizeY) * 0.5f);

                int x = (mpos.x - a->transform.pos.x) / TileSizeX;
                int y = (mpos.y - a->transform.pos.y) / TileSizeY;

                //Check what room we are hovering
                if (ru::DistCheck(roomCenter, mpos, ru::GetDistance(sf::Vector2f(a->transform.pos.x, a->transform.pos.y), roomCenter)))
                {
                    //Perform AABB
                    if (ru::AABB(mpos, a->transform.pos, sf::Vector2f(a->size.x * TileSizeX, a->size.y * TileSizeY)))
                    {
                        //Change the tile at location
                        //editor->renderer->Deregister(a->tiles[x + a->size.x * y]->GetComponent<ru::SpriteComponent>());
                        //a->tiles[x + a->size.x * y]->GetComponent<ru::SpriteComponent>().renderID = -1;
                        ru::RectangleComponent& rectComp = a->tiles[(GroupType)(layer)][x + a->size.x * y]->AddComponent<ru::RectangleComponent>();
                        rectComp.rect.pos = a->tiles[(GroupType)(layer)][x + a->size.x * y]->GetComponent<ru::TransformComponent>().transform.pos;
                        rectComp.rect.sizex = TileSizeX;
                        rectComp.rect.sizey = TileSizeY;
                        rectComp.awake = true;
                        editor->pm->Register(&rectComp);

                        ru::DebugBox& dBox = a->tiles[(GroupType)(layer)][x + a->size.x * y]->AddComponent<ru::DebugBox>();
                        dBox.rectangle.setFillColor(sf::Color::Transparent);
                        dBox.rectangle.setOutlineColor(sf::Color::Green);
                        dBox.rectangle.setOutlineThickness(1.0f);
                        editor->renderer->Register(dBox);
                    }
                }
            }
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

    if (ImGui::Button("Erase", ImVec2(ButtonWidth, ButtonHeight)))
    {
        toolState = ERASE;
    }

    //New Room Popup
    ImGui::SetNextWindowSize(ImVec2(300, 230));
    if (ImGui::BeginPopupModal("New Room"))
    {
        static int size[2];
        static float position[2];
        static const char* preview = "none";
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
                    tilemapTexturePreview = &editor->rm->GetTexture(std::string(preview));
                    
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
            map->SetTileMap(std::string(preview));
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
    if (ImGui::Button("Collider", ImVec2(ButtonWidth, ButtonHeight)))
    {
        toolState = COLLIDER;
    }

    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(1560, 20));
    ImGui::SetNextWindowSize(ImVec2(500, 950));
    ImGui::Begin("Editor", &editor->isMapEditorOpen);

    const char* editors[] = { "Map Editor", "Object Viewer", "Generation" };
    static int ctab = (int)currentTab;
    ImGui::Combo("Tab", &ctab, editors, IM_ARRAYSIZE(editors));
    currentTab = static_cast<EditorTabs>(ctab);

    ImGui::Separator();

    if (currentTab == TILEMAP)
    {
        ImGui::Text("Selected Room");
        bool posChange = false;

        //ImGui::InputInt2(": Position", roomPos, 16);
        if (ImGui::InputFloat(": X", &roomPos[0], TileSizeX, TileSizeX))
        {
            posChange = true;
        }

        if (ImGui::InputFloat(": Y", &roomPos[1], TileSizeX, TileSizeX))
        {
            posChange = true;
        }

        if (selectedRoom)
        {
            selectedRoom->transform.pos.x = roomPos[0];
            selectedRoom->transform.pos.y = roomPos[1];

                if (posChange)
                {
                    for(int i = 0; i < GroupsAmount; i++)
                    for (ru::Tile* t : selectedRoom->tiles[(GroupType)(i)])
                    {
                        sf::Vector2f nPos = t->GetComponent<ru::TransformComponent>().transform.pos;
                        nPos.x = roomPos[0] + (t->coords.x * TileSizeX);
                        nPos.y = roomPos[1] + (t->coords.y * TileSizeY);

                        t->GetComponent<ru::TransformComponent>().transform.pos = nPos;
                    }
                    posChange = false;
                }
        }

        if (ImGui::Button("Delete"))
        {
            //Delete tiles from room
            for (int i = 0; i < selectedRoom->tiles.size(); i++)
            {
                editor->renderer->Deregister(selectedRoom->tiles[(GroupType)(layer)][i]->GetComponent<ru::SpriteComponent>().renderID, 
                                             selectedRoom->tiles[(GroupType)(layer)][i]->GetComponent<ru::SpriteComponent>().layer);
            }

            std::vector<ru::Room*>& rooms = map->GetRooms();

            for (std::vector<ru::Room*>::const_iterator a = rooms.begin(); a != rooms.end(); ++a )
            {
                if (*a == selectedRoom)
                {
                    delete(*a);
                    map->GetRooms().erase(a);
                    break;
                }
            }
                //Deregister tiles from renderer

            //Delete room from map
        }

        ImGui::Separator();

        //Layer
        ImGui::DragInt("Layer",&layer, 1.0f,0,4);

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
                        tilemapTexturePreview = &editor->rm->GetTexture(textures_items[n]);
                        
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
                        
                        /*if (!editor->renderer->isRegistered(key))
                        {
                            editor->renderer->RegisterSprite(*tilePreview, 1);
                        }*/
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
            static const char* preview = "none";
            if (ImGui::BeginCombo(": Maps", preview))
            {

                for (int n = 0; n < map_items.size(); n++)
                {

                    bool is_selected;
                    if (preview != nullptr)
                        is_selected = (preview == map_items[n]);
                    else
                        is_selected = true;

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

    /*        ////Clears current map and opens map.
            //if (ImGui::Button("Load"))
            //{

            //    //@TODO: Clear Map

            //    /*std::string s = 
            //    int a = std::stoi(s);
            //    //Get Map Resource and generate usuable file for Scene.
            //    //map = editor->rm->GetMap(preview);

            //    //Add Entire map to rendering
            //    sf::Texture& tex = editor->rm->GetTexture(map->GetTileMap());

            //    for (auto& r : map->GetRooms())
            //    {
            //        for (auto t : r->tiles)
            //        {
            //            t = new ru::Tile(&tex);
            //            //Get texture
            //            //t->texture = new TextureResource;
            //            //t->texture->texture = new sf::Texture();
            //            //t->texture->texture = editor->rm->GetTexture(r.second->tilemapName)->texture;
            //            //t->sprite.setTexture(*t->texture->texture);

            //            editor->renderer->Register(t->GetComponent<ru::SpriteComponent>());
            //        }
            //    }

            //    ImGui::CloseCurrentPopup();
            //}*/

            //Import takes all the rooms within the map and moves them into the currently open map
            
            if (ImGui::Button("Load"))
            {
                if(!map)
                    NewMap();

                ru::resource::Map* r_map = editor->rm->GetMap(std::string(preview));
                map->SetTileMap(r_map->tilemapName);

                sf::Texture& tex = editor->rm->GetTexture(r_map->tilemapName);

                for (auto& r : r_map->rooms)
                {
                    ru::Room* room = new ru::Room();
                    room->AddComponent<ru::TransformComponent>();
                    room->size = r->size;
                    room->GetComponent<ru::TransformComponent>().transform = r->transform;

                    for (auto& t : r->tiles)
                    {
                        ru::Tile* tile = new ru::Tile(&tex);
                        ru::SpriteComponent t_spr = tile->GetComponent<ru::SpriteComponent>();
                        t_spr.sprite.setTextureRect(t->textureRect);
                        tile->GetComponent<ru::TransformComponent>().transform = t->transform;
                        tile->coords = sf::Vector2u(t->coord.x, t->coord.y);


                        //editor->renderer->Register(tile->GetComponent<ru::SpriteComponent>());

                        editor->eManager->AddEntity(tile, GroupType::Background);

                        room->tiles[(GroupType)(layer)].push_back(tile);
                    }

                    map->AddRoom(room);
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
            std::string name = std::string(buffer);
            //editor->rm->SaveAsset<ru::Map>(name, map, ru::ResourceType::MAP);

            editor->rm->SaveAsset(name, map);
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

    map = new ru::Map(editor->game->GetBaseSystem());

    editor->game->world->map = map;
}

void MapEditor::NewRoom(unsigned int sizex_, unsigned int sizey_, float posx_, float posy_, std::string TileMap)
{
    if (!map)
    {
        std::cout << "[ERROR]No Map instance found, creating a new map." << std::endl;
        NewMap();
    }

    static int mapid = 0;

    sf::Texture* tex = &editor->rm->GetTexture(TileMap);

    //make sure that spot on map is empty
  /*  while (map->rooms[mapid])
    {
        mapid++;
    }*/

    ru::Room* room = new ru::Room;
    room->AddComponent<ru::TransformComponent>();
    room->GetComponent<ru::TransformComponent>().transform.pos = sf::Vector2f(posx_, posy_);

    room->size = sf::Vector2i(sizex_, sizey_);

    for (int i = 0; i < sizey_; i++)
    {
        for (int j = 0; j < sizex_; j++)
        {
            for (int l = 0; l < GroupsAmount; l++)
            {
                ru::Tile* tile = new ru::Tile(tex);
                editor->eManager->AddEntity(tile, GroupType::Background);
                tile->GetComponent<ru::SpriteComponent>().layer = 0;
                tile->GetComponent<ru::SpriteComponent>().renderID = -1;
                //editor->renderer->Register(tile->GetComponent<ru::SpriteComponent>());
                tile->GetComponent<ru::SpriteComponent>().sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(0, 0)));
                tile->GetComponent<ru::TransformComponent>().transform.pos = sf::Vector2f((j * TileSizeX) + posx_,
                    (i * TileSizeY) + posy_);
                tile->coords = sf::Vector2u(j, i);
                // tile->size = sf::Vector2u(TileSizeX, TileSizeY);
                room->tiles[(GroupType)(l)].push_back(tile);

                if(editor->game->GetCurrentState() == GameStates::INEDITOR)
                if (l == 0)
                {
                    ru::DebugBox db = tile->AddComponent<ru::DebugBox>();
                    db.rectangle.setPosition(tile->GetComponent<ru::TransformComponent>().transform.pos);
                    db.rectangle.setSize(sf::Vector2f(32.0f, 32.0f));
                    db.rectangle.setOutlineColor(sf::Color::White);
                }
            }
        }
    }

    editor->eManager->AddEntity(room, GroupType::Base);

    map->AddRoom(room);
    mapid++;
}

void MapEditor::RefreshAssets()
{
    if (tileMapAssetId != "")
    {
        //tilemap = editor->rm->GetTexture(tileMapAssetId)->texture;

        if (!map)
            return;

        for (auto& a : map->GetRooms())
        {
            for (auto& t : a->tiles[(GroupType)(layer)])
            {
                t->GetComponent<ru::SpriteComponent>().sprite.setTexture(*tilemap);
            }
        }
    }
};