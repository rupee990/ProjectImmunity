#pragma once

#include "Engine.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <map>
#include "World/World.h"

class Entity;


namespace ru { class Engine; }


#define GroupsAmount 5

enum GroupType
{
    Base = 0,
    Background = 1,
    Phyisical = 2,
    Above = 3,
    UI = 4
};

namespace ru
{
    class World;
}

class Component
{
public:

    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}

    virtual ~Component() {};

    Entity* entity;
};

inline std::size_t GetComponentId()
{
    static int lastId = 0;
    return lastId++;
}

template<typename T>
inline std::size_t GetComponentId() noexcept
{
    static std::size_t TypeId = GetComponentId();
    return TypeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Entity
{
public:
    void Update()
    {
        if(active)
            for (auto& c : components) c->Update();
    }

    void Draw()
    {
        if(active)
            for (auto& c : components) c->Draw();
    }

    bool isActive() { return active; }
    void Destroy() { active = false; }

    template<typename T>
    bool HasComponent()
    {
        return bitset[GetComponentId<T>()];
    }

    template<typename T, typename ...tArgs>
    T& AddComponent(tArgs&&... args)
    {
        T* c(new T(std::forward<tArgs>(args)...));
        c->entity = this;
        std::unique_ptr<Component>uPtr{ c };
        components.emplace_back(std::move(uPtr));

        bitset[GetComponentId<T>()] = true;
        componentsArray[GetComponentId<T>()] = c;

        c->Init();
        return *c;
    }

    template<typename T>
    T& GetComponent() 
    {
        auto ptr(componentsArray[GetComponentId<T>()]);
        return *static_cast<T*>(ptr);
    };

    
public:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentsArray;
    ComponentBitSet bitset;

    ru::World* world;
};

namespace ru
{
    class Engine;
}

class EntityManager
{
public:

    EntityManager(ru::Engine* _engine)
    {
        m_engine = _engine;
    }

    void Update()
    {
        Refresh();

        for (int i = 0; i < 5; i++)
        {
            for (std::unique_ptr<Entity>& e : groupedEntities[(GroupType)(i)])
            {
                e->Update();
            }
        }

        Refresh();
    }

    void Draw()
    {
        for (int i = 0; i < 5; i++)
        {
            for (std::unique_ptr<Entity>& e : groupedEntities[(GroupType)(i)])
            {
                e->Draw();
            }
        }
    }

    void Refresh()
    {
        for (int i = 0; i < 5; i++)
        {
            groupedEntities[(GroupType)(i)].erase(std::remove_if(std::begin(groupedEntities[(GroupType)(i)]), std::end(groupedEntities[(GroupType)(i)]),
                [](const std::unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }),
                std::end(groupedEntities[(GroupType)(i)]));
        }
    }

    Entity& AddEntity()
    {
        Entity* e = new Entity();
        e->world = world;
        std::unique_ptr<Entity> ePtr{ e };
        entities.emplace_back(std::move(ePtr));

        return *e;
    }

    void AddEntity(Entity* entity)
    {
        entity->world = world;
        std::unique_ptr<Entity> ePtr{ entity };
        entities.emplace_back(std::move(ePtr));
    }

    void AddEntity(Entity* entity, GroupType type)
    {
        entity->world = world;
        std::unique_ptr<Entity> ePtr{ entity };
        //entities.emplace_back(std::move(ePtr));

        groupedEntities[type].emplace_back(std::move(ePtr));
    }

public:
    ru::World* world;
    std::vector<std::unique_ptr<Entity>> entities;
    std::map<GroupType, std::vector<std::unique_ptr<Entity>>> groupedEntities;

    ru::Engine* m_engine;
};