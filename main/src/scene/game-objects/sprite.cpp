#include "sprite.hpp"

namespace ast
{
    bool& Sprite::getVisible()
    {
        return this->_visible;
    }

    SpriteTexture& Sprite::getTexture()
    {
        return this->_texture;
    }

    void Sprite::setVisible(bool value)
    {
        this->_visible = value;
    }

    void Sprite::setTexture(SpriteTexture value)
    {
        this->_texture = value;
    }

    Sprite::Sprite() : _visible(true), _texture(SpriteTexture()) 
    {
        this->_name = "Sprite";
        this->_position = {.0f, .0f};
        this->_texture = SpriteTexture();
        this->_updatable = true;

        this->_type = SPRITE;
    }

    Sprite::Sprite(const char* name = "Sprite", glm::vec2 position = {.0f, .0f}, SpriteTexture texture = SpriteTexture(), bool updatable = true) : _visible(true), _texture(texture) 
    {
        this->_name = name;
        this->_position = position;
        this->_texture = texture;
        this->_updatable = updatable;

        this->_type = SPRITE;
    }
} // namespace ast