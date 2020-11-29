#include "../spriteTexture.hpp"
#include "TransformObject.hpp"

namespace ast
{
    class Sprite : public TransformObject
    {
    protected:
        bool _visible;
        SpriteTexture _texture;

    public:
        bool& getVisible();
        SpriteTexture& getTexture();

        void setVisible(bool value);
        void setTexture(SpriteTexture value);

        Sprite();
        Sprite(const char* name, glm::vec2 position, SpriteTexture texture, bool updatable);
    };
} // namespace ast