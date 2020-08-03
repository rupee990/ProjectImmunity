#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include "System/RuBaseClass.h"
#include "Resource.h"

namespace ru
{
    class Map;
    class Engine;
}

namespace ru
{
    class ResourceManager : public RUClass
    {
    public:
        ResourceManager(ru::Engine* a_engine);
        ~ResourceManager();

        void LoadAssets(std::string filepath);

        /*  template <typename T>*/
         /* void SaveAsset(std::string name, ru::resource::rInterface type);*/


        void SaveAsset(std::string name, ru::Map* ptr);

        sf::Texture& GetTexture(std::string name);
        sf::Texture& GetTexture(int id);
        void SetTexture(std::string name, sf::Texture& texture);

        ru::resource::Map*                  GetMap(int id);        
        ru::resource::Map*                  GetMap(std::string name);

        std::vector<ru::resource::Map*>     GetMaps();

        std::vector<std::string> GetResourceNames(ru::ResourceType type);

        ru::resource::Texture* GetTextureResource(int id);

        int GetSize(ru::ResourceType type) { return sizes[type]; }


    private:
        int managerID = 0;
        std::map<ru::ResourceType, int> sizes;
        std::unordered_map<std::string, ru::resource::rInterface*> resources;
    };
}