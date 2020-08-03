#pragma once

#include "GraphicsComponents.h"
#include "DebugRenderingComponents.h"
#include <unordered_map>
#include <map>
//#include "../Resources/Resource.h"

namespace sf
{
    class RenderWindow;
}

namespace ru
{
    class SpriteComponent;
    class Engine;
}

namespace ru
{
    class Renderer
    {
    public:
        Renderer(Engine* _engine, sf::RenderWindow* _win);
        ~Renderer() {};

        void Update();
        void Render();
        //static void Render(sf::Drawable& drawable);

        void Register(ru::SpriteComponent& _sprComp);
        void Register(ru::DebugBox& _debugBox);
        void RegisterSprite(sf::Sprite& sprite, int layer);
        void Deregister(int id, int _layer);
        void Deregister(const ru::SpriteComponent _sprComp);

        bool isRegistered(int id) { return registeredSprites.find(id) != registeredSprites.end(); }
        bool isRegistered(ru::SpriteComponent _sprComp);

    private:
        sf::RenderWindow* window;
        unsigned int registerID = 0;

        ru::Engine* m_engine;
        
        std::map<int, std::vector<sf::Drawable*>> registeredSprites;
    };
}