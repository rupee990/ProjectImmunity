#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow* win_)
{
    window = win_;
}

Renderer::~Renderer()
{

}

uint Renderer::RegisterObject(sf::Drawable* object)
{
    registeredObjects[renderIds] = object;

    renderIds++;

    return renderIds - 1;
}

void Renderer::DeRegisterObject(uint key)
{
    //delete(registeredObjects[key]);
    registeredObjects.erase(key);
}

void Renderer::Render()
{
    for (auto& a : registeredObjects)
    {
        window->draw(*a.second);
    }
}

