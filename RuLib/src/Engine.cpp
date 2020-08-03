#include "Engine.h"
#include <assert.h>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <filesystem>
#include <iostream>
#include <fstream>

//Include Core Headers
#include "Graphics/Renderer.h"
#include "Editor/Editor.h"
#include "Physics/PhysicsManager.h"
#include "Scripting/ScriptManager.h"
#include "Resources/ResourceManager.h"
#include "System/ECS.h"
#include "System/Input.h"
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;


//Here we can activate and deactivate systems
#define ENABLE_RESOURCEMANAGER true
#define ENABLE_PHYSICSMANAGER true
#define ENABLE_RENDERER true
#define ENABLE_EDITOR true
#define ENABLE_SCRIPTMANAGER false
#define ENABLE_ENTITYMANAGER true
#define ENABLE_INPUTMANAGER true



ru::Engine::Engine(sf::RenderWindow* a_win)
{
    m_window = a_win;
}

ru::Engine::~Engine()
{

}

void ru::Engine::StartEngine()
{
    //Initialize resource manager;
    if (ENABLE_RESOURCEMANAGER)
    {
        m_resourceManager = new ru::ResourceManager(this);
        m_resourceManager->LoadAssets(fs::current_path().string() + "/Assets");
    }

    //Initialize Renderer
    if(ENABLE_RENDERER)
        m_renderer = new ru::Renderer(this, m_window);

    //Initialize PhysicsManager
    if(ENABLE_PHYSICSMANAGER)
        m_physicsManager = new PhysicsManager(this);

    //Initialize ScriptManager
    //TODO: Finish Implementation of ScriptManager

    //Initialize entity manager
    if(ENABLE_ENTITYMANAGER)
        m_entityManager = new EntityManager(this);

    //Initialize editor
    if (ENABLE_EDITOR)
    {
        m_editor = new ru::Editor(this);
        m_editor->InitializeEditor();
    }

    //Initialize Inputs
    if(ENABLE_INPUTMANAGER)
        m_inputManager = new InputManager(this);

}

void ru::Engine::ShutdownEngine()
{   

    //TODO: Add better clean up
}

ru::Renderer* ru::Engine::GetRenderer()
{
    if (!ENABLE_RENDERER)
        return nullptr;

    assert(m_renderer != nullptr);
    return m_renderer;
}

EntityManager* ru::Engine::GetEntityManager()
{
    if (!ENABLE_ENTITYMANAGER)
        return nullptr;

    assert(m_entityManager != nullptr);
    return m_entityManager;
}

PhysicsManager* ru::Engine::GetPhysicsManager()
{
    if (!ENABLE_PHYSICSMANAGER)
        return nullptr;

    assert(m_physicsManager != nullptr);
    return m_physicsManager;
}

InputManager* ru::Engine::GetInputManager()
{
    if (!ENABLE_INPUTMANAGER)
        return nullptr;

    assert(m_inputManager != nullptr);
    return m_inputManager;
}

ru::ResourceManager* ru::Engine::GetResourceManager()
{
    if (!ENABLE_RESOURCEMANAGER)
        return nullptr;

    assert(m_resourceManager != nullptr);
    return m_resourceManager;
}

ru::Editor* ru::Engine::GetEditor()
{
    if (!ENABLE_EDITOR)
        return nullptr;

    assert(m_editor != nullptr);
    return m_editor;
}
