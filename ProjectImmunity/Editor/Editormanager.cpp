#include "EditorManager.h"
#include "../Core/Map.h"

#include "../Imgui/imgui-SFML.h"
#include "../Imgui/imgui.h"
#include "../Core/Managers/ResourceManager.h"
#include "../Core/Renderer.h"
#include "MapEditor.h"
 
Editor::Editor(ResourceManager* rm_, Renderer* renderer_, sf::RenderWindow* window_)
{
    rm = rm_;
    window = window_;
    renderer = renderer_;

    //Initialize editors
    mapEditor = new MapEditor(this);
}

Editor::~Editor()
{

}

void Editor::Update(float dt)
{
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

        }
        if (ImGui::MenuItem("Pause"))
        {

        }
        if (ImGui::MenuItem("Stop"))
        {

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

