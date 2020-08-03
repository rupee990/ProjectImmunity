#pragma once

#include "SFML/Graphics.hpp"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Object;

class Camera
{
public:
    Camera(sf::RenderWindow* window_, sf::Event* _event, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f size_ = sf::Vector2f(1920.0f, 1080.0f));
    ~Camera();

    //void Init(sf::Vector2f position, sf::Vector2f size_, sf::RenderWindow* window_);
    void Update(float dt);

    void SetCameraPos(sf::Vector2f pos_) { view->setCenter(pos_); }
    void SetViewPortSize(sf::Vector2f size_) { view->setSize(size_); }
    void SetFocus(Object* fo);

    sf::Vector2f GetCameraPos() { return view->getCenter(); }
    sf::Vector2f GetViewPortSize() { return view->getSize(); }
    sf::View*    GetView() { return view; }
    Object*      GetFocusObj() { return focusObj; }

    void HandleEvent(sf::Event& event);

    //Keep Editor Size and Position for when moving out of game
    sf::Vector2f edit_pos, edit_size;

private:

    //If true then set the center to the focusObj else camera is in free roam.
    bool isFocusing;

    sf::Event* event;

    //View From Camera
    sf::View* view;
    sf::RenderWindow* win;

    Object* focusObj;

    //For Camera Movement
    bool firstClick = false;
    sf::Vector2f initPos;

};