#include "Core/Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Immunity Project"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Default, sf::ContextSettings(32));
    window->setVerticalSyncEnabled(true);
    window->setActive(true);

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

    Game* game = new Game(window);

    while (window->isOpen())
    {
        game->Update(0.0f);
        game->Render();
    }

    return 0;
}