#include "sprite.hpp"

namespace ast
{
    unsigned int Sprite::spriteIdCounter;

    unsigned int& Sprite::getChunkID()
    {
        return this->_chunkID;
    }

    float& Sprite::getTileID()
    {
        return this->_tileID;
    }

    float& Sprite::getTextureID()
    {
        return this->_textureID;
    }

    unsigned int& Sprite::getSpriteID()
    {
        return this->_spriteID;
    }

     void Sprite::setChunkID(unsigned int value)
    {
        this->_chunkID = value;
    }

    void Sprite::setTextureID(float value)
    {
        this->_textureID = value;
    }

    void Sprite::setTileID(float value)
    {
        this->_tileID = value;
    }

    Sprite::Sprite(const char* name, glm::vec3 position, float textureID, float tileID, unsigned int chunkID, bool updatable) :  
        _spriteID(Sprite::spriteIdCounter),
        _chunkID(chunkID)
    {
        Sprite::spriteIdCounter++;

        this->_name = name;
        this->_position = position;
        this->_textureID = textureID;
        this->_tileID = tileID;
        this->_updatable = updatable;

        this->_type = SPRITE;
    }
} // namespace ast