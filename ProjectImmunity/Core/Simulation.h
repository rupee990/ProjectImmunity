#pragma once

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

class Simulation
{
public:
    Simulation(sf::RenderWindow* win_);
    ~Simulation();

    void Update();
    void Render();

private:
    sf::RenderWindow* window;
    sf::Clock* clock;

    //Imgui Menu bools
    bool isProgramMenuOpen = false;

    //Managers
    ResourceManager* resourceManager;
    Renderer* renderer;

    //Editor
    Editor* editor;

};