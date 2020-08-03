#include "Resources/ResourceManager.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <ostream>

#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"

#include "World/Map.h"
#include "World/Room.h"
#include "World/Tile.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

ru::ResourceManager::ResourceManager(ru::Engine* a_engine) 
    : RUClass(a_engine)
{
}

ru::ResourceManager::~ResourceManager()
{

}
//
//template <typename T>
//void ru::ResourceManager::SaveAsset(std::string name, ru::resource::rInterface type)
//{
//    T asset = static_cast<T>(type);
//
//    /*DO saving stuff*/
//
//
//}

void ru::ResourceManager::SaveAsset(std::string name, ru::Map* ptr)
{
     std::string filepath = fs::current_path().string() + "/Assets/Maps/" + name + ".map";
     std::ofstream os(filepath, std::ofstream::out);
     cereal::JSONOutputArchive archive(os);

     ru::resource::Map map;
     map.name = name;
     map.tilemapName = ptr->GetTileMap();
     map.numberOfRooms = 0;

     for (auto r : ptr->GetRooms())
     {
         ru::resource::Room* rRoom = new ru::resource::Room;
         rRoom->size = r->size;
         rRoom->transform = r->GetComponent<ru::TransformComponent>().transform;

         for (int i = 0; i < GroupsAmount; i++)
         {
             for (auto t : r->tiles[(GroupType)(i)])
             {
                 ru::resource::Tile* tile = new ru::resource::Tile;
                 tile->transform = t->GetComponent<ru::TransformComponent>().transform;
                 tile->textureRect = t->GetComponent<ru::SpriteComponent>().sprite.getTextureRect();

                 tile->coord = sf::Vector2i(t->GetComponent<ru::TransformComponent>().transform.pos.x / TileSizeX, t->GetComponent<ru::TransformComponent>().transform.pos.y / TileSizeY);

                 rRoom->tiles.push_back(tile);
             }
         }

         map.rooms.push_back(rRoom);
         map.numberOfRooms++;
     }

    if (os.is_open())
    {
      /* ru::Map* map = static_cast<ru::Map*>(ptr);*/

       map.save(archive);

       for (auto r : map.rooms)
       {
           r->save(archive);
           for (auto t : r->tiles)
           {
               t->save(archive);
           }
       }
    }
}

void ru::ResourceManager::LoadAssets(std::string _filepath)
{
    //Start Iterator on filepath
    for (auto & p : fs::directory_iterator(_filepath))
    {
        fs::path path(p);

        if (fs::exists(path))
            std::cout << " exists\n";
        else
            std::cout << " does not exist\n";

        //Check if folder
        if (fs::is_directory(path))
        {
            LoadAssets(path.string());
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
            //MapResource* mr = new MapResource;
            //mr->map = new Map(renderer);

            //mr->load(archive);

            ru::resource::Map* map = new ru::resource::Map();

            //ADD FOR LOOP FOR TILE
            map->load(archive);

            for (int i = 0; i < map->numberOfRooms; i++)
            {
                ru::resource::Room* rRoom = new ru::resource::Room();

                rRoom->load(archive);

                for (int j = 0; j < rRoom->size.x * rRoom->size.y; j++)
                { 
                    ru::resource::Tile* t = new ru::resource::Tile;

                    t->load(archive);

                    rRoom->tiles.push_back(t);
                }

                map->rooms.push_back(rRoom);
            }

            map->type = ru::ResourceType::MAP;

            sizes[ru::ResourceType::MAP] += 1;
            resources.insert({ path.stem().string(), map });
            /*for (int i = 0; i < mr->numberOfRooms; i++)
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

                mr->map->rooms[i] = rr->room;
            }

            mr->id = managerIds;

            maps[managerIds] = mr;

            managerIds++;*/

        }
        if (extension == ".png" || extension == ".jpg")
        {
            //USE SFML TEXTURE LOADER
            sf::Texture* texture = new sf::Texture;
            ru::resource::Texture* t = new ru::resource::Texture(*texture);
                                                                   
            t->id = managerID;
            t->name = path.stem().string();
            t->type = ru::ResourceType::TEXTURE;
            t->texture.loadFromFile(path.string());

            sizes[ru::ResourceType::TEXTURE] += 1;
            resources.insert({ t->name, t });
            managerID++;

        }
        if (extension == ".ru")
        {
            //Access scriptManager and load in script
            //criptmanager->LoadScripts(path.string());
        }

        else if (extension == ".robj")
        {
            //USE CEREAL
            /*cereal::JSONInputArchive archive(stream);
            ObjectResource* obj = new ObjectResource;
            obj->load(archive);
            obj->id = managerIds;

            objects[managerIds] = obj;
            managerIds++;*/
        }
    }
}

sf::Texture & ru::ResourceManager::GetTexture(int id)
{
    for (std::unordered_map<std::string, ru::resource::rInterface*>::const_iterator iter = resources.begin(); iter != resources.end(); iter++)
    {
        if (iter->second->id == id)
            return static_cast<ru::resource::Texture*>(iter->second)->texture;
    }

    sf::Texture tex;
    return tex;
}

ru::resource::Texture* ru::ResourceManager::GetTextureResource(int id)
{
    for (std::unordered_map<std::string, ru::resource::rInterface*>::const_iterator iter = resources.begin(); iter != resources.end(); iter++)
    {
        if (iter->second->id == id)
            return static_cast<ru::resource::Texture*>(iter->second);
    }
}

ru::resource::Map* ru::ResourceManager::GetMap(int id)
{
    for (auto a : resources)
    {
        if (a.second->id == id)
            return static_cast<ru::resource::Map*>(a.second);
    }
};

ru::resource::Map* ru::ResourceManager::GetMap(std::string name)
{
    return static_cast<ru::resource::Map*>(resources[name]);
}

void ru::ResourceManager::SetTexture(std::string name, sf::Texture& texture)
{
    static_cast<ru::resource::Texture*>(resources[name])->texture = texture;
}

sf::Texture& ru::ResourceManager::GetTexture(std::string name)
{
    return static_cast<ru::resource::Texture*>(resources[name])->texture;
}

std::vector<std::string> ru::ResourceManager::GetResourceNames(ru::ResourceType type)
{
    std::vector<std::string> names;

    for (auto a : resources)
    {
        if (a.second->type == type)
            names.push_back(a.second->name);
    }

    return names;
}