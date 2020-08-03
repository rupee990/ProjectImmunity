#pragma once

//#include <ECS.h>
//#include "Transform.h"
//#include <SFML/Graphics.hpp>
//#include "Utilities.h"
//#include "Renderer.h"
//#include "Managers/Resource.h"
//#include "Managers/ResourceManager.h"

//namespace ru
//{
//    class HealthComponent : public Component
//    {
//        int health = 100;
//    };
//
//    class SpriteComponent : public Component
//    {
//    //public:
//    //    SpriteComponent(sf::Texture* _tex, Renderer* _renderer) : texture(_tex), renderer(_renderer)
//    //    {
//    //        spr.setTexture(*texture);
//
//    //        if(_renderer)
//    //            renderId = renderer->RegisterObject(&spr);
//    //    };
//
//    //    ~SpriteComponent()
//    //    {
//    //        renderer->DeRegisterObject(renderId);
//    //    }
//
//    //    void Update() override
//    //    {
//    //        //If there is a transform Update position
//    //        if (entity->HasComponent<TransformComponent>())
//    //        {
//    //            TransformComponent transform = entity->GetComponent<TransformComponent>();
//
//    //            spr.setPosition(sf::Vector2f(transform.pos.x, transform.pos.y));
//    //        }
//    //    }
//
//    //public:
//    //    sf::Texture* texture;
//    //    sf::Sprite spr;
//
//    //    Renderer* renderer;
//    //    unsigned int renderId;
//    };
//
//    class PlayerMovementComponent : public Component
//    {
//    //public:
//    //    PlayerMovementComponent(sf::Event* _event)
//    //    {
//    //        sfEvent = _event;
//    //    }
//
//    //    void Update(sf::Event& e)
//    //    {
//    //        //ON KeyPressed
//    //        if (e.type == sf::Event::KeyPressed)
//    //        {
//    //            if (e.key.code == sf::Keyboard::W)
//    //            {
//    //                direction[0] = true;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::S)
//    //            {
//    //                direction[1] = true;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::D)
//    //            {
//    //                direction[2] = true;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::A)
//    //            {
//    //                direction[3] = true;
//    //            }
//    //        }
//
//    //        //ON Key release
//    //        else if (e.type == sf::Event::KeyReleased)
//    //        {
//    //            if (e.key.code == sf::Keyboard::W)
//    //            {
//    //                direction[0] = false;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::S)
//    //            {
//    //                direction[1] = false;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::D)
//    //            {
//    //                direction[2] = false;
//    //            }
//
//    //            if (e.key.code == sf::Keyboard::A)
//    //            {
//    //                direction[3] = false;
//    //            }
//    //        }
//
//    //        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
//    //        {
//    //            firing = true;
//    //        }
//    //    }
//
//    //    const std::bitset<4> GetDirections() { return direction; }
//    //    bool& isFiring() { return firing; }
//    //    
//    //private:
//    //    std::bitset<4> direction;
//    //    bool firing = false;
//    //    sf::Event* sfEvent;
//
//    };
//
//    class ProjectileComponent : public Component
//    {
//    public:
//    //    ProjectileComponent( sf::Vector2f _startPos, sf::Vector2f _direction, float _speed) : direction(_direction), speed(_speed), initialPos(_startPos)
//    //    {
//    //        clock.restart();
//    //    }
//
//    //    void Init()
//    //    {
//    //        ru::TransformComponent& transform = entity->GetComponent<ru::TransformComponent>();
//    //        transform.pos.x = initialPos.x;
//    //        transform.pos.y = initialPos.y;
//
//    //        ru::SpriteComponent& sprite = entity->GetComponent<ru::SpriteComponent>();
//    //        sprite.spr.setPosition(transform.pos);
//    //    }
//
//    //    void Update() override
//    //    {
//    //        //Check lifetime
//    //        lifetime -= clock.getElapsedTime().asSeconds();
//
//    //        if (lifetime <= 0.0f)
//    //            entity->Destroy();
//
//    //        //Move Towards Direction
//    //        ru::TransformComponent& transform = entity->GetComponent<ru::TransformComponent>();
//    //        transform.pos.x = transform.pos.x + (direction.x * speed);
//    //        transform.pos.y = transform.pos.y + (direction.y * speed);
//
//    //    }
//    //public:
//
//    //    sf::Vector2f initialPos;
//    //    float lifetime = 5.0f;
//    //    sf::Clock clock;
//    //    sf::Vector2f direction;
//    //    float speed;
//    };
//
//    //Player Component
//
//    class PlayerComponent : public Component
//    {
//    public:
//
//    //    PlayerComponent(float _speed, EntityManager* _eManager, Renderer* _renderer, ResourceManager* _rManager) : speed(_speed), eManager(_eManager),renderer(_renderer), rManager(_rManager) 
//    //    {
//    //        rManager = _rManager;
//    //    
//    //    };
//
//    //    void Update() override
//    //    {
//    //        HandleControls();
//    //    }
//
//    //    void HandleControls()
//    //    {
//    //        if (entity->HasComponent<PlayerMovementComponent>() && entity->HasComponent<SpriteComponent>())
//    //        {
//    //            //Get Components needed
//    //            PlayerMovementComponent& input = entity->GetComponent<PlayerMovementComponent>();
//    //            SpriteComponent& sprite = entity->GetComponent<SpriteComponent>();
//
//    //            std::bitset<4> direction = input.GetDirections();
//    //            sf::Vector2f cPos = sf::Vector2f(sprite.spr.getPosition().x, sprite.spr.getPosition().y);
//
//    //            sf::Vector2i m = renderer->GetRenderTarget().mapCoordsToPixel(cPos);
//
//    //            if (direction[0] == true)
//    //            {
//    //                cPos.y -= speed;
//    //            }
//    //            else if (direction[1] == true)
//    //            {
//    //                cPos.y += speed;
//    //            }
//    //            
//    //            if (direction[2] == true)
//    //            {
//    //                cPos.x += speed;
//    //            }
//    //            else if (direction[3] == true)
//    //            {
//    //                cPos.x -= speed;
//    //            }
//
//    //            sprite.spr.setPosition(cPos.x, cPos.y);
//
//    //            if (input.isFiring())
//    //            {
//    //                if (firingrate <= 0.0f)
//    //                {
//    //                    sf::Vector2f mPos = renderer->GetRenderTarget().mapPixelToCoords(sf::Mouse::getPosition());
//    //                    fireDirection = ru::GetDirection(sf::Vector2f(m.x, m.y), mPos);
//
//    //                    Entity& Projectile(eManager->AddEntity());
//    //                    Projectile.AddComponent<ru::TransformComponent>();
//    //                    Projectile.AddComponent<ru::SpriteComponent>(&rManager->GetTexture("Projectile")->texture, renderer);
//    //                    Projectile.AddComponent<ru::ProjectileComponent>(cPos, fireDirection, 15.0f);
//
//    //                    input.isFiring() = false;
//    //                    firingrate = 1.0f;
//    //                }
//    //                else
//    //                {
//    //                    firingrate -= 0.1f;
//    //                    input.isFiring() = false;
//    //                }
//    //            }
//    //        }
//    //    }
//
//    //public:
//    //    float speed;
//    //    float firingrate;
//
//    //    sf::Vector2f fireDirection = sf::Vector2f(0.0f, 1.0f);
//
//    //    Renderer* renderer;
//    //    EntityManager* eManager;
//    //    ResourceManager* rManager;
//    //};
//    };