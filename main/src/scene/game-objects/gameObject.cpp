#include "gameObject.hpp"

namespace ast
{
    unsigned int GameObject::_idCounter;

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