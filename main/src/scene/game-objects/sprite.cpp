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

    float& Sprite::getTileID()
    {
        return this->_tileID;
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

    void Sprite::setTileID(float value)
    {
        this->_tileID = value;
    }

    Sprite::Sprite(const char* name, glm::vec3 position, SpriteTexture texture, float tileID, unsigned int chunkID, bool updatable) :  
        _spriteID(Sprite::spriteIdCounter),
        _chunkID(chunkID),
        _visible(true), _texture(texture) 
    {
        Sprite::spriteIdCounter++;

        this->_name = name;
        this->_position = position;
        this->_texture = texture;
        this->_tileID = tileID;
        this->_updatable = updatable;

        this->_type = SPRITE;
    }
} // namespace ast