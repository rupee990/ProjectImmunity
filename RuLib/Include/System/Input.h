#pragma once

#include "System/ECS.h"
#include "SFML/Graphics.hpp"

/*
* player controller
* Contains keys to be used
*/

struct KeyInfo
{
    sf::Keyboard::Key key;
    sf::Mouse::Button button;
    bool isPressed = false;

};

namespace ru
{
    class PlayerControllerComponent : public Component
    {
    public:
        PlayerControllerComponent() {};
        ~PlayerControllerComponent() {};

        void AddQueueKey(sf::Keyboard::Key key, std::string tag)
        {
            keys[tag].key = key;
            keys[tag].isPressed = false;
        }

        void AddQueueKey(sf::Mouse::Button _button, std::string tag)
        {
            keys[tag].button = _button;
            keys[tag].isPressed = false;
        }

        void Update() override
        {

        };

        KeyInfo GetKey(std::string name)
        {
            return keys[name];
        }

        std::map<std::string, KeyInfo> keys;
    };
};

class InputManager
{
public:
    InputManager(ru::Engine* a_engine)
    {
        m_engine = a_engine;
    }

    ~InputManager()
    {

    }

    void Init()
    {
        //Get keyBinding in settings.r file
    }

    void Update(sf::Event& event)
    {
        if (event.type == sf::Event::EventType::KeyPressed)
        {
            for (auto& k : controller->keys)
            {
                if (event.key.code == k.second.key)
                {
                    k.second.isPressed = true;
                }
            }
        }

        if (event.type == sf::Event::EventType::KeyReleased)
        {
            for (auto& k : controller->keys)
            {
                if (event.key.code == k.second.key)
                {
                    k.second.isPressed = false;
                }
            }
        }

        if (event.type == sf::Event::EventType::MouseButtonPressed)
        {
            for (auto& k : controller->keys)
            {
                if (event.key.code == k.second.button)
                {
                    k.second.isPressed = true;
                }
            }
        }

        if (event.type == sf::Event::EventType::MouseButtonReleased)
        {
            for (auto& k : controller->keys)
            {
                if (event.key.code == k.second.button)
                {
                    k.second.isPressed = false;
                }
            }
        }


    }

    KeyInfo GetKey(std::string name)
    {
        return controller->keys[name];
    }

    void SetController(ru::PlayerControllerComponent* _contr)
    {
        controller = _contr;
    }

    ru::PlayerControllerComponent* GetController() { return controller; }

private:
    ru::PlayerControllerComponent* controller;
    //sf::RenderWindow* window;

    ru::Engine* m_engine;
};

