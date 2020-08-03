#pragma once

namespace ru
{
    class Renderer;
    class ResourceManager;
    class Editor;
}

class EntityManager;
class PhysicsManager;
class InputManager;

//SFML classes
namespace sf
{
    class RenderWindow;
}

namespace ru
{
    class Engine
    {
    public:
        Engine(sf::RenderWindow* a_win);
        ~Engine();

        void                    StartEngine();
        void                    ShutdownEngine();

        ru::Renderer* GetRenderer();
        EntityManager* GetEntityManager();
        PhysicsManager* GetPhysicsManager();
        InputManager* GetInputManager();
        ru::ResourceManager* GetResourceManager();
        ru::Editor* GetEditor();


    private:
        //All Core system are stored here, all these are read only
        ru::Renderer* m_renderer;
        EntityManager* m_entityManager;
        PhysicsManager* m_physicsManager;
        InputManager* m_inputManager;
        ru::ResourceManager* m_resourceManager;
        ru::Editor* m_editor;
        sf::RenderWindow* m_window;

    };
}