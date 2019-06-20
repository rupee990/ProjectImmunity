#pragma once

#include "SFML/Window/Event.hpp"

namespace sf
{
    class Window;
    class RenderWindow;
    class Sprite;
    class Clock;
}

class ResourceManager;
class Editor;
class Renderer;
class Camera;
class EntityManager;


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

    void Update();
    void Render();

    void ChangeGameState(GameStates _newstate) { gamestate = _newstate; }

private:
    sf::RenderWindow* window;
    sf::Clock* clock;

    //Imgui Menu bools
    bool isProgramMenuOpen = false;

    //Managers
    ResourceManager* resourceManager;
    Renderer* renderer;
    EntityManager* eManager;

    GameStates gamestate = INEDITOR;

    sf::Event event;

    //Editor
    Editor* editor;
    Camera* camera;
};