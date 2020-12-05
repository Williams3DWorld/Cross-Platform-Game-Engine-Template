#include "spriteTexture.hpp"

namespace ast
{
    bool& SpriteTexture::isRepeat()
    {
        return this->_repeat;
    }

    float& SpriteTexture::getUOffset()
    {
        return this->_uOffset;
    }

    float& SpriteTexture::getVOffset()
    {
        return this->_vOffset;
    }

    float& SpriteTexture::getUScale()
    {
        return this->_uScale;
    }
    float& SpriteTexture::getVScale()
    {
        return this->_vScale;
    }
    float& SpriteTexture::getTextureID()
    {
        return this->_textureID;
    }

    void SpriteTexture::setUOffset(float value)
    {
        this->_uOffset = value;
    }
    void SpriteTexture::setVOffset(float value)
    {
        this->_vOffset = value;
    }
    void SpriteTexture::setUScale(float value)
    {
        this->_uScale = value;
    }
    void SpriteTexture::setVScale(float value)
    {
        this->_vScale = value;
    }
    void SpriteTexture::setTextureID(float value)
    {
        this->_textureID = value;
    }

    SpriteTexture::SpriteTexture() : _repeat(false), _uOffset(.0f), _vOffset(.0f), _uScale(1.f), _vScale(1.f), _textureID(0) {}
    SpriteTexture::SpriteTexture(float textureID = .0f, float uOffset = .0f, float vOffset = .0f, float uScale = 1.f, float vScale = 1.f, bool repeat = false) : _repeat(repeat), _uOffset(uOffset), _vOffset(vOffset), _uScale(uScale), _vScale(vScale), _textureID(textureID) {}

} // namespace ast