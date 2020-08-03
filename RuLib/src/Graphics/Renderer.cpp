#include "Graphics/Renderer.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Graphics/GraphicsComponents.h"
#include "Engine.h"

ru::Renderer::Renderer(ru::Engine* _engine, sf::RenderWindow* _win)
{
    m_engine = _engine;
    window = _win;
}

void ru::Renderer::Register(ru::SpriteComponent& _sprComp)
{
    registeredSprites[_sprComp.layer].push_back(&_sprComp.sprite);
    _sprComp.renderID = registerID;
    registerID++;
}

void ru::Renderer::Register(ru::DebugBox & _debugBox)
{
    registeredSprites[0].push_back(&_debugBox.rectangle);
}

void ru::Renderer::RegisterSprite(sf::Sprite& sprite, int layer)
{
    registeredSprites[layer][registerID] = &sprite;
    registerID++;
}

void ru::Renderer::Deregister(int _id, int _layer)
{
    /*DEREGISTER FROM MAP*/

    

}

void ru::Renderer::Deregister(const ru::SpriteComponent _sprComp)
{
    /*DEREGISTER FROM MAP*/
    for (auto& a : registeredSprites)
    {
        for (int i = 0; i < a.second.size(); i++)
        {
            if ((sf::Sprite*)(a.second[i]) == &_sprComp.sprite)
            {
                std::vector<sf::Drawable*>::const_iterator it = a.second.begin();

                it += i;

                a.second.erase(it);
            }
        }
    }
}

bool ru::Renderer::isRegistered(ru::SpriteComponent _sprComp)
{
    for (auto& a : registeredSprites)
    {
        for (int i = 0; i < a.second.size(); i++)
        {
            if ((sf::Sprite*)(a.second[i]) == &_sprComp.sprite)
            {
                return true;
            }
        }
    }

    return false;
}

void ru::Renderer::Update()
{
    /* Clean any sprite that doesnt need to be rendered.*/
}

void ru::Renderer::Render()
{
    int index = 0;

    for (int l = -5; l < 5; l++)
    {
        if (!registeredSprites[l].empty())
        {
            for (auto& s : registeredSprites[l])
            {
                window->draw(*s);
            }
        }
    }
}

//void ru::Renderer::Render(sf::Drawable & drawable)
//{
//    /*sf::RenderWindow::draw(drawable);*/
//    window->draw(drawable);
//}


