#include "ObjectManager.h"

#include "../Object.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Update()
{
    //Update Objects registered To object manager.
}

void ObjectManager::AddObject(sf::Vector2f pos_, sf::Texture& texture_)
{
    Object* object = new Object();

    object->sprite.setPosition(pos_);
    object->sprite.setTexture(texture_);


}

void ObjectManager::AddObject(Object& object)
{

}