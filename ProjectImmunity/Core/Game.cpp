#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Managers/ResourceManager.h"
#include "../Editor/Tile.h"
#include "../Editor/EditorManager.h"
#include "../Core/Renderer.h"
#include "../Global.h"
#include "Camera.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"

#include <ECS.h>
#include "GameComponents.h"

#include <filesystem>

namespace fs = std::experimental::filesystem;

Game::Game(sf::RenderWindow* win_) : window(win_)
{
    ImGui::SFML::Init(*win_);
    
    clock = new sf::Clock();

    resourceManager = new ResourceManager();
    resourceManager->LoadAllAssets(fs::current_path().string() + "/Assets");

    renderer = new Renderer(win_);

    editor = new Editor(this, resourceManager, renderer, win_);

    camera = new Camera(win_, &event);

    eManager = new EntityManager();

    //Create Player Entity
    Entity& player(eManager->AddEntity());
    player.AddComponent<ru::PlayerComponent>(5.0f, eManager, renderer, resourceManager);
    player.AddComponent<ru::SpriteComponent>(resourceManager->GetTexture("Hacker"), renderer);
    player.AddComponent<ru::PlayerMovementComponent>(&event);
}

Game::~Game()
{

}

void Game::Update()
{
    sf::Time dt = clock->restart();

    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (camera->GetFocusObj() == nullptr)
        {
            //Check for Zoom
            if (event.type == sf::Event::MouseWheelMoved)
            {
                //Zoom works by increasing the size of the view.
                if (event.mouseWheel.delta > 0)
                {
                    camera->SetViewPortSize(sf::Vector2f(camera->GetViewPortSize().x - (16.0f * 2), camera->GetViewPortSize().y - (9.0f * 2)));
                }
                else if (event.mouseWheel.delta < 0)
                {
                    camera->SetViewPortSize(sf::Vector2f(camera->GetViewPortSize().x + (16.0f * 2), camera->GetViewPortSize().y + (9.0f * 2)));
                }
            }
            //Check for Movement

        }
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }



    if (gamestate == INGAME)
    {
        //Update Entity Manager
    }
    else if (gamestate == INEDITOR)
    {
        
    }

    //Update imgui
    ImGui::SFML::Update(*window, dt);

    eManager->Update();

    editor->Update(dt.asSeconds());

    //Update Camera
    camera->Update(dt.asSeconds());

}

void Game::Render()
{
    window->clear();

    window->setView(*camera->GetView());

    renderer->Render(); //Game Objects

    editor->Render(); //Render Imgui 

    window->display();
}