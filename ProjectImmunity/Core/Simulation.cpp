#include "Simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Managers/ResourceManager.h"
#include "../Editor/Tile.h"
#include "../Editor/EditorManager.h"
#include "../Core/Renderer.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"

#include <filesystem>

namespace fs = std::experimental::filesystem;

Simulation::Simulation(sf::RenderWindow* win_) : window(win_)
{
    ImGui::SFML::Init(*win_);
    
    clock = new sf::Clock();

    resourceManager = new ResourceManager();
    resourceManager->LoadAllAssets(fs::current_path().string() + "/Assets");

    renderer = new Renderer(win_);

    editor = new Editor(resourceManager, renderer, win_);

}

Simulation::~Simulation()
{

}

void Simulation::Update()
{
    sf::Time dt = clock->restart();

    sf::Event event;
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }

    //Update imgui
    ImGui::SFML::Update(*window, dt);

    editor->Update(dt.asSeconds());

}

void Simulation::Render()
{
    window->clear();

    renderer->Render(); //Game Objects

    editor->Render(); //Render Imgui 

    window->display();
}