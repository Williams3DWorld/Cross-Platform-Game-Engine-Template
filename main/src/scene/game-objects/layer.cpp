#include "layer.hpp"
#include <iostream>
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

    void Layer::setBufferData(std::vector<std::any>& vertexData, std::vector<unsigned int>& indexData)
    {
        GLsizei compSize = sizeof(float);
        const auto numAttribs = 7;
        std::vector<AttributeElement> attribElementData({
            {GL_FLOAT, 3, compSize},
            {GL_FLOAT, 2, compSize},
            {GL_FLOAT, 1, compSize},
            {GL_FLOAT, 1, compSize},
        });

        Attribute attribData = {numAttribs, attribElementData};
        this->vbo = std::make_shared<ast::OpenGLBatch>(vertexData, indexData, attribData);
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
       // if (this->vbo)
            this->vbo->bind(this->textureID);
    }

    Layer::Layer(const char* name, unsigned int id, glm::vec3 position, unsigned int textureID, bool updatable)
    {
        this->_type = LAYER;
        this->_name = name;
        this->_layerID = id;
        this->textureID = textureID;
    }
} // namespace ast