#pragma once

#include <string>
#include <map>
#include <assert.h>

#include "../../Global.h"
#include "cereal/archives/json.hpp"
#include "Resource.h"

class Object;
class Map;

namespace sf
{
    class Texture;
}

class ResourceManager
{
public:
    ResourceManager();
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
    MapResource* GetMap(int id);
    MapResource* GetMap(std::string);

    //Returns the number of elements in a map of type.
    int GetSizeByType(ResourceType type);

public:
    std::map<int, MapResource*>     maps;

private:
    //Ids that are distributed to assets.
    uint managerIds = 0;

    std::unordered_map<int, TextureResource*> textures;
    std::unordered_map<int, ObjectResource*>  objects;
    //std::map<int, MapResource*>     maps;

};