#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include "cereal/archives/json.hpp"
//#include <ScriptManager.h>

#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

ResourceManager::ResourceManager(Renderer* _renderer, EntityManager* _eManager)
{
    scriptmanager = new ScriptManager();
    eManager = _eManager;
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::LoadAllAssets(std::string path_)
{
    //Start Iterator on filepath
    for (auto & p : fs::directory_iterator(path_))
    {
        fs::path path(p);

        if (fs::exists(path))
            std::cout << " exists\n";
        else
            std::cout << " does not exist\n";

        //Check if folder
        if (fs::is_directory(path))
        {
            LoadAllAssets(path.string());
        }

        std::string extension = path.extension().string();
        std::string filepath = path.string();
        std::ifstream stream(path.string(), std::ifstream::in);
       
        //Check type of file
        if (extension == ".map")
        {
            if (!stream.is_open())
            {
                return;
            }

            //Load Map data and store it in list
            cereal::JSONInputArchive archive(stream);
            MapResource* mr = new MapResource;
            //mr->map = new Map(renderer);
            
            mr->load(archive);
            //ADD FOR LOOP FOR TILE

            for (int i = 0; i < mr->numberOfRooms; i++)
            {
                RoomResource* rr = new RoomResource;
                //rr->room = new Room();

                rr->load(archive);

                mr->rooms.push_back(rr);

                for (int j = 0; j < rr->size.x * rr->size.y; j++)
                {
                    TileResource* tr = new TileResource;
                    //tr->tile = new Tile();

                    Tile& tile(static_cast<Tile&>(eManager->AddEntity()));

                    tr->load(archive);
                    //tile.GetComponent<ru::Transform>().pos = tr->position;
                    //tile.GetComponent<ru::SpriteComponent>().spr.setTextureRect(tr->texRect);

                    mr->rooms[i]->tiles.push_back(tr);
                }

                /*mr->map->rooms[i] = rr->room;*/
            }

            mr->id = managerIds;

            maps[managerIds] = mr;

            managerIds++;
        }
        if (extension == ".png" || extension == ".jpg")
        {
            //USE SFML TEXTURE LOADER
            TextureResource* t = new TextureResource;
            t->id = managerIds;
            t->name = path.stem().string();
            t->texture.loadFromFile(path.string());

            textures[managerIds] = t;
            managerIds++;

        }
        if (extension == ".ru")
        {
            //Access scriptManager and load in script
            scriptmanager->LoadScripts(path.string());
        }

        else if (extension == ".robj")
        {
            //USE CEREAL
            cereal::JSONInputArchive archive(stream);
            ObjectResource* obj = new ObjectResource;
            obj->load(archive);
            obj->id = managerIds;

            objects[managerIds] = obj;
            managerIds++;
        }
    }
}

void ResourceManager::LoadAssetsByType(std::string path, ResourceType type)
{

}

void ResourceManager::LoadAsset(std::string path, std::string filename)
{

}

void ResourceManager::SaveAllAssets(std::string path)
{
    //Save All Maps.
    std::string mapPath = path + "/Maps";

    for (auto& a : maps)
    {
        std::string filename = mapPath + "/" + a.second->name + ".map";
        std::ofstream of(filename, std::ofstream::out);

        {
            cereal::JSONOutputArchive archive(of);

            a.second->save(archive);
        }
    }
}

void ResourceManager::SaveAsset(Map* map, std::string filename_)
{
    //Open file path
    std::string mapPath = fs::current_path().string() + "/Assets/Maps";
    std::string filename = mapPath + "/" + filename_ + ".map";

    std::ofstream of(filename, std::ofstream::out);
    cereal::JSONOutputArchive archive(of);

    MapResource* mr = new MapResource();
    mr->numberOfRooms = map->rooms.size();
    mr->name = filename_;
    //mr->map = map;
    mr->save(archive);

    for (auto& r : map->rooms)
    {
        RoomResource*rr = new RoomResource;
        /*rr->room = r.second;*/
        rr->position = map->position;
        rr->size = map->size;

        rr->save(archive);

        for (auto& t : r.second->tiles)
        {
            TileResource* tr = new TileResource;
            tr->coord = t->coord;
            tr->position = t->GetComponent<ru::Transform>().pos;
            tr->texRect = t->GetComponent<ru::SpriteComponent>().spr.getTextureRect();
            tr->save(archive);
        }
    }
}

TextureResource* ResourceManager::GetTexture(int id)
{
    if (textures.find(id) != textures.end())
    {
        assert(textures[id]);
        return textures[id];
    }

    return nullptr;
}

TextureResource* ResourceManager::GetTexture(std::string name)
{
    for (auto a : textures)
    {
        if(a.second->name == name)
        {
            return a.second;
        }
    }

    return nullptr;
}

ObjectResource * ResourceManager::GetObject(int id)
{
    return nullptr;
}

ObjectResource * ResourceManager::GetObject(std::string)
{
    return nullptr;
}

Map* ResourceManager::GetMap(int id)
{
    Map* map = new Map(renderer);



    //return maps[id];

}

Map* ResourceManager::GetMap(std::string name)
{
    Map* map = new Map(renderer);



    for (auto a : maps)
    {
        if (a.second->name == name)
        {
            

            for (auto& r : a.second->rooms)
            {
                sf::Texture* tex = GetTexture(r->tilemapName)->texture;

                for (auto& t : r->tiles)
                {
                    map->AddTile(t->position, sf::Vector2i(32,32), *tex);
                }
            }
        }
    }

    return map;
}

int ResourceManager::GetSizeByType(ResourceType type)
{
    switch (type)
    {
    case TEXTURE:
        return textures.size();
    
    case OBJECT:
        return objects.size();

    case MAP:
        return maps.size();
    }

    return 0;
}
