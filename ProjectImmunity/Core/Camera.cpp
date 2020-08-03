#include "Camera.h"
#include "Object.h"

#include "System/Utilities.h"

Camera::Camera(sf::RenderWindow* window_, sf::Event* _event, sf::Vector2f position, sf::Vector2f size_)
{
    win = window_;
    event = _event;
    view = new sf::View(position, size_);
    win->setView(*view);
}

Camera::~Camera()
{

}

//@TODO: CAMERA SMOOTH MOVEMENT USING LINEAR INTERPOLATION
//NOTE: DO NOT USE DECIMAL VALUES TO MOVE THE VIEW.
void Camera::Update(float dt)
{
    if (!focusObj && firstClick)
    {
        //Get Mouse Position and move in direction and distance
        sf::Vector2f mPos = sf::Vector2f(sf::Mouse::getPosition());

        sf::Vector2f direction = ru::GetDirection(sf::Vector2f(initPos.x, initPos.y), sf::Vector2f(mPos.x, mPos.y));
        float dist = ru::GetDistance(sf::Vector2f(initPos.x, initPos.y), sf::Vector2f(mPos.x, mPos.y));

        SetCameraPos(direction * -dist);
    }
}

void Camera::SetFocus(Object* fo)
{
    if (fo == nullptr)
    {
        isFocusing = false;
    }
    else
    {
        isFocusing = true;
    }

    focusObj = fo;
}

void Camera::HandleEvent(sf::Event & event)
{
    if (focusObj != nullptr)
    {
        view->setCenter(sf::Vector2f(std::floor(focusObj->sprite.getPosition().x + 0.5), std::floor(focusObj->sprite.getPosition().y + 0.5)));
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (!firstClick)
            {
                firstClick = true;

                //Get Initial Position
                initPos = sf::Vector2f(sf::Mouse::getPosition()) + GetCameraPos();
            }
        }

        //Check for Zoom
        if (event.type == sf::Event::MouseWheelMoved)
        {
            //Zoom works by increasing the size of the view.
            if (event.mouseWheel.delta > 0)
            {
                SetViewPortSize(sf::Vector2f(GetViewPortSize().x - (16.0f * 2), GetViewPortSize().y - (9.0f * 2)));
            }
            else if (event.mouseWheel.delta < 0)
            {
                SetViewPortSize(sf::Vector2f(GetViewPortSize().x + (16.0f * 2), GetViewPortSize().y + (9.0f * 2)));
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            firstClick = false;
        }
    }
}
