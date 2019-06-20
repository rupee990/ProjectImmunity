#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Entity;

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
};

class EntityManager
{
public:

    void Update()
    {
        Refresh();

        for (int i = 0; i < entities.size(); i++)
        {
            if(entities[i] != nullptr)
                if(entities[i]->isActive())
                    entities[i]->Update();
        }

        Refresh();
    }

    void Draw()
    {
        for (auto& a : entities)
        {
            if(a  != nullptr)
                if(a->isActive())
                    a->Draw();
        }
    }

    void Refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
            [](const std::unique_ptr<Entity> &mEntity) 
        {
            return !mEntity->isActive(); 
        }), 
            std::end(entities));
    }

    Entity& AddEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> ePtr{ e };
        entities.emplace_back(std::move(ePtr));

        return *e;
    }

public:
    std::vector<std::unique_ptr<Entity>> entities;
};