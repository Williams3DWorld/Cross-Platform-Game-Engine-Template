#include "sprite.hpp"

namespace ast
{
    unsigned int Sprite::spriteIdCounter;

    unsigned int& Sprite::getChunkID()
    {
        return this->_chunkID;
    }

    bool& Sprite::getVisible()
    {
        return this->_visible;
    }

    unsigned int& Sprite::getSpriteID()
    {
        return this->_spriteID;
    }

    SpriteTexture& Sprite::getTexture()
    {
        return this->_texture;
    }

     void Sprite::setChunkID(unsigned int value)
    {
        this->_chunkID = value;
    }

    void Sprite::setVisible(bool value)
    {
        this->_visible = value;
    }

    void Sprite::setTexture(SpriteTexture value)
    {
        this->_texture = value;
    }

    Sprite::Sprite(     const char* name = "Sprite", 
                        unsigned int chunkID = 0, 
                        glm::vec3 position = glm::vec3(.0f), 
                        SpriteTexture texture = SpriteTexture(), 
                        bool updatable = true) :  
        _spriteID(Sprite::spriteIdCounter),
        _chunkID(chunkID),
        _visible(true), _texture(texture) 
    {
        Sprite::spriteIdCounter++;

        this->_name = name;
        this->_position = position;
        this->_texture = texture;
        this->_updatable = updatable;

        this->_type = SPRITE;
    }
} // namespace ast