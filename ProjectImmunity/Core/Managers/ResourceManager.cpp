#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include "cereal/archives/json.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

ResourceManager::ResourceManager()
{

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
            mr->map = new Map();
            
            mr->load(archive);
            //ADD FOR LOOP FOR TILE

            for (int i = 0; i < mr->numberOfRooms; i++)
            {
                RoomResource* rr = new RoomResource;
                rr->room = new Room();

                rr->load(archive);

                for (int j = 0; j < rr->room->size.x * rr->room->size.y; j++)
                {
                    TileResource* tr = new TileResource;
                    tr->tile = new Tile();

                    tr->load(archive);
                    tr->tile->sprite.setPosition(tr->position);
                    tr->tile->sprite.setTextureRect(tr->texRect);

                    rr->room->tiles.push_back(tr->tile);
                }

                mr->map->rooms[i] = rr->room;
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
            t->texture = new sf::Texture;
            t->texture->loadFromFile(path.string());

            textures[managerIds] = t;
            managerIds++;

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
    mr->map = map;
    mr->save(archive);

    for (auto& r : map->rooms)
    {
        RoomResource*rr = new RoomResource;
        rr->room = r.second;
        rr->save(archive);

        for (auto& t : r.second->tiles)
        {
            TileResource* tr = new TileResource;
            tr->tile = t;
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

MapResource * ResourceManager::GetMap(int id)
{
    return maps[id];
}

MapResource * ResourceManager::GetMap(std::string name)
{
    for (auto a : maps)
    {
        if (a.second->name == name)
        {
            return a.second;
        }
    }
    return nullptr;
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
