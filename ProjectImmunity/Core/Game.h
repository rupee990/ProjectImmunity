#pragma once

#include "SFML/Window/Event.hpp"

namespace sf
{
    class Window;
    class RenderWindow;
    class Sprite;
    class Clock;
}

namespace ru
{
    class Renderer;
    class ResourceManager;
    class Camera;
    class World;
    class Engine;
}

class PhysicsManager;
class Player;
class InputManager;
class ResourceManager;
class Editor;
class Renderer;

class EntityManager;
class BaseSystems;

enum GameStates
{
    INEDITOR = 0,
    INGAME,
};

class Game
{
public:
    Game(sf::RenderWindow* win_);
    ~Game();

    void Update(float _dt);
    void Render();

    void ChangeGameState(GameStates _newstate) 
    { 
        gamestate = _newstate; 
    };

    GameStates GetCurrentState() { return gamestate; }

    BaseSystems* GetBaseSystem()
    {
        return baseSys;
    };

public:
    ru::World* world;

private:
    sf::RenderWindow* window;
    sf::Clock* clock;

    //Imgui Menu bools
    bool isProgramMenuOpen = false;

    BaseSystems* baseSys;

    //Managers
    ru::ResourceManager* resourceManager;
    ru::Renderer* renderer;
    EntityManager* eManager;
    PhysicsManager* pManager;

    GameStates gamestate = INEDITOR;

    sf::Event event;

    //Editor
    Editor* editor;
    ru::Camera* camera;

    Player* player;
    InputManager* inputmanager;

    ru::Engine* m_engine;
};