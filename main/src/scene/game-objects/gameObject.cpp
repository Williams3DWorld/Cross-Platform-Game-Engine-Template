#include "gameObject.hpp"

namespace ast
{
    unsigned int GameObject::_idCounter;
    std::unordered_map<const char*, std::shared_ptr<GameObject>> GameObjectPool::gameObjects;

    uint16_t& GameObject::getType()  {
        return this->_type;
    }

    const char* GameObject::getName()
    {
        return this->_name;
    }

    unsigned int& GameObject::getID()
    {
        return this->_id;
    }

    std::unordered_map<const char*, std::shared_ptr<GameObject>>& GameObject::getChildren()
    {
        return this->_children;
    }

    void GameObject::setName(const char* value) 
    {
        this->_name = value;
    }
    
    GameObject::GameObject() : _type(NONE),
                               _id(GameObject::_idCounter),
                               _name(""),
                               _parent(nullptr)
    {
        GameObject::_idCounter++;
    }
}