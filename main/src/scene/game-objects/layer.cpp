#include "layer.hpp"

namespace ast
{
    unsigned int& Layer::getTextureID()
    {
        return this->textureID;
    }

    void Layer::setTextureID(unsigned int value)
    {
        this->textureID = value;
    }

    void Layer::addChild(std::shared_ptr<GameObject>& value)
    {
        this->_children[value->getName()] = value;
    }

    void Layer::update(float dt)
    {
        for (auto object : this->_children)
        {
            if (object.second->getType() == SPRITE)
                std::dynamic_pointer_cast<Sprite>(object.second)->update(dt);
        }
    }

    void Layer::render()
    {
        for (auto object : this->_children)
        {
            if (object.second->getType() == SPRITE)
                std::dynamic_pointer_cast<Sprite>(object.second)->render();
        }
    }

    Layer::Layer(const char* name, unsigned int id, glm::vec3 position, unsigned int textureID, bool updatable)
    {
        this->_type = LAYER;
        this->_name = name;
        this->_layerID = id;
        this->textureID = textureID;
    }
} // namespace ast