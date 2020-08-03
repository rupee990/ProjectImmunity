#pragma once

#include <string>
#include <map>
#include <assert.h>

#include "../../Global.h"
#include "cereal/archives/json.hpp"
#include "Resource.h"

#include <filesystem>

class ScriptManager;

namespace fs = std::experimental::filesystem;

class Object;
class Map;
class EntityManager;
class Renderer;

namespace sf
{
    class Texture;
}

class ResourceManager
{
public:
    ResourceManager(Renderer* _renderer, EntityManager* eManager);
    ~ResourceManager();

    //Asset Loading
    void LoadAllAssets(std::string path = "/Assets");
    void LoadAssetsByType(std::string path, ResourceType type); //Used for Reloading
    void LoadAsset(std::string path, std::string filename); //Uses the windows explorer to load.

    //Asset Saving
    void SaveAllAssets(std::string path = "/Assets");
    void SaveAsset(Map* map, std::string filename);

    //Textures Getters
    TextureResource* GetTexture(int id);
    TextureResource* GetTexture(std::string name);

    //Object Getters
    ObjectResource* GetObject(int id);
    ObjectResource* GetObject(std::string);

    //Map Getters
    Map* GetMap(int id);
    Map* GetMap(std::string);

    //Returns the number of elements in a map of type.
    int GetSizeByType(ResourceType type);

    void ReloadAssets() 
    {
        managerIds = 0;
        LoadAllAssets(fs::current_path().string() + "/Assets");
    }

public:
    std::map<int, MapResource*>     maps;

private:
    //Ids that are distributed to assets.
    unsigned int managerIds = 0;

    std::unordered_map<int, TextureResource*> textures;
    std::unordered_map<int, ObjectResource*>  objects;
    //std::map<int, MapResource*>     maps;

    ScriptManager* scriptmanager;
    Renderer* renderer;
    EntityManager* eManager;
};