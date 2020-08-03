#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
//#include "Managers/ResourceManager.h"
#include "../Editor/Tile.h"
#include "../Editor/EditorManager.h"
#include "../Core/Renderer.h"
#include "../Global.h"
#include "Camera.h"

#include "../Imgui/imgui.h"
#include "../Imgui/imgui-SFML.h"

#include "Resources/ResourceManager.h"
#include "Graphics/GraphicsComponents.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"
#include "System/Utilities.h"
#include "System/Input.h"
#include "World/Player.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponents.h"
#include "World/World.h"

#include <System/ECS.h>
//#include "GameComponents.h"

#include <filesystem>

#include "Engine.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Game::Game(sf::RenderWindow* win_)
{
    gamestate = GameStates::INEDITOR;

    clock = new sf::Clock();

    window = win_;

    m_engine = new ru::Engine(win_);
    m_engine->StartEngine();

    world = new ru::World();
    world->window = win_;

    renderer = m_engine->GetRenderer();

    eManager = m_engine->GetEntityManager();
    eManager->world = world;

    resourceManager = m_engine->GetResourceManager();

    camera = new ru::Camera(window);
    inputmanager = m_engine->GetInputManager();

    pManager = m_engine->GetPhysicsManager();

    world = new ru::World();
    world->window = window;

    sf::Texture& t = resourceManager->GetTexture("Ghost");
    player = new Player();
    eManager->AddEntity(player, GroupType::Phyisical);
    player->AddComponent<ru::TransformComponent>();
    player->AddComponent<ru::PhysicsMovementComponent>();
    player->AddComponent<ru::DebugBox>();
    //player->world = world;

    player->AddComponent<ru::SpriteComponent>(t, 1);
    renderer->Register(player->GetComponent<ru::SpriteComponent>());

    ru::RectangleComponent& rect = player->AddComponent<ru::RectangleComponent>();
    rect.phys_type = DYNAMIC;
    rect.col_type = RECTANGLE;
    rect.rect.sizex = 32.0f;
    rect.rect.sizey = 32.0f;
    rect.rect.pos.x -= 32.0f;
    rect.rect.pos.y -= 32.0f;
    rect.awake = true;
    pManager->Register(&rect);

    ru::PlayerControllerComponent& p_controller = player->AddComponent<ru::PlayerControllerComponent>();
    p_controller.AddQueueKey(sf::Keyboard::W, "Forward");
    p_controller.AddQueueKey(sf::Keyboard::S, "Backward");
    p_controller.AddQueueKey(sf::Keyboard::A, "Left");
    p_controller.AddQueueKey(sf::Keyboard::D, "Right");
    //p_controller.AddQueueKey(sf::Mouse::Button::Left, "L-Mouse");

    inputmanager->SetController(&p_controller);

    ImGui::SFML::Init(*win_);
    editor = new Editor(this, resourceManager, renderer, window, eManager, pManager);
    world->map = editor->map;
}

Game::~Game()
{

}

void Game::Update(float _dt)
{
    sf::Time dt = clock->restart();
    if (gamestate == GameStates::INEDITOR)
    {
        ImGui::SFML::Update(*window, dt);
    }

    sf::Event event;

    if (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        camera->HandleEvent(event);

        if (event.type == sf::Event::Closed)
        {
            window->close();
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                gamestate = GameStates::INEDITOR;
            }
        }

        inputmanager->Update(event);
    }

    if (gamestate == GameStates::INGAME)
    {
        player->Update(dt.asSeconds());
        pManager->Update();
    }

    eManager->Update();

    camera->Update(dt.asSeconds());

    if (gamestate == GameStates::INEDITOR)
    {
        editor->Update(dt.asSeconds());
    }
}

void Game::Render()
{
    window->clear();

    window->setView(*camera->GetView());

    eManager->Draw();

    

    //renderer->Render();

    if (gamestate == GameStates::INEDITOR)
    {
        editor->Render();
    }

    window->display();
}

