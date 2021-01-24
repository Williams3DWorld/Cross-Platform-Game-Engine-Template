#include "spriteLayer.hpp"
#include <iostream>
#include "../../application/opengl/opengl-asset-manager.hpp"

namespace ast
{
    unsigned int& SpriteLayer::getTextureID()
    {
        return this->textureID;
    }

    void SpriteLayer::setTextureID(unsigned int value)
    {
        this->textureID = value;
    }

    void SpriteLayer::setBufferData(std::vector<float>& vertexData, std::vector<unsigned int>& indexData)
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

    void SpriteLayer::addChild(std::shared_ptr<GameObject>& value)
    {
        this->_children[value->getName()] = value;
    }

    void SpriteLayer::update(float dt)
    {
        for (auto object : this->_children)
            std::dynamic_pointer_cast<Sprite>(object.second)->update(dt);
    }

    void SpriteLayer::render(unsigned int matrix_location, glm::mat4 camera_matrix)
    {
        OpenGLAssetManager::get().getTexture(0).bind();
        this->vbo->bind();
    }

    SpriteLayer::SpriteLayer(const char* name, unsigned int id, glm::vec3 position, unsigned int textureID, bool updatable)
    {
        this->_type = LAYER;
        this->_name = name;
        this->_layerID = id;
        this->textureID = textureID;
    }
} // namespace ast