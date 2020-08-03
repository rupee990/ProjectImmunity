#include "EditorManager.h"
#include "../Core/Map.h"

#include "../Imgui/imgui-SFML.h"
#include "../Imgui/imgui.h"
//#include "../Core/Managers/ResourceManager.h"
#include "../Core/Renderer.h"
#include "MapEditor.h"

#include "../Core/Game.h"
 
Editor::Editor(Game* _game, ru::ResourceManager* rm_, ru::Renderer* renderer_, sf::RenderWindow* window_, EntityManager* _eManager, PhysicsManager* _pManager)
{
    game = _game;
    eManager = _eManager;
    rm = rm_;
    window = window_;
    renderer = renderer_;
    pm = _pManager;

    //Initialize editors
    mapEditor = new MapEditor(this);
}

Editor::~Editor()
{

}

void Editor::Update(float dt)
{
    //If Window is into focus, reload assets
    if (window->hasFocus())
    {
        if (hasFocusOnce)
        {
            hasFocusOnce = false;
            //rm->ReloadAssets();

            mapEditor->RefreshAssets();
        }
    }
    else
    {
        hasFocusOnce = true;
    }

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Project"))
    {
        if (ImGui::MenuItem("New"))
        {
            //@TODO: New Project Window
        }
        if (ImGui::MenuItem("Load"))
        {

        }
        if (ImGui::MenuItem("Save"))
        {

        }

        ImGui::Separator();
        if (ImGui::MenuItem("Exit"))
        {
            window->close();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Editor"))
    {
        if (ImGui::MenuItem("New Map"))
        {
            mapEditor->NewMap();
        }

        if (ImGui::MenuItem("Import Tilemap"))
        {

        }
        
        if (ImGui::MenuItem("Reload Assets"))
        {

        }

        if (ImGui::MenuItem("Active Auto Reload"))
        {

        }

        if (ImGui::MenuItem("Clear Map"))
        {
            //DeRegister Maps
            //renderer->DeRegisterObject();
        }

        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Simulation"))
    {
        if (ImGui::MenuItem("Start"))
        {
            game->ChangeGameState(INGAME);
        }
        if (ImGui::MenuItem("Pause"))
        {

        }
        if (ImGui::MenuItem("Stop"))
        {
            game->ChangeGameState(INEDITOR);
        }
        ImGui::EndMenu();

    }
    ImGui::EndMainMenuBar();

    //Update Editors
    mapEditor->Update(dt);
    mapEditor->UpdateEditorUI(dt);

}

void Editor::Render()
{
    ImGui::SFML::Render(*window);
}

