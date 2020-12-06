#include "../spriteTexture.hpp"
#include "TransformObject.hpp"

namespace ast
{
    class Sprite : public TransformObject
    {
    private:
        static unsigned int spriteIdCounter;

    protected:
        bool _visible;
        unsigned int _spriteID;
        unsigned int _chunkID;
        SpriteTexture _texture;

    public:
        bool& getVisible();
        unsigned int& getSpriteID();
        unsigned int& getChunkID();
        SpriteTexture& getTexture();

        void setVisible(bool value);
        void setChunkID(unsigned int value);
        void setTexture(SpriteTexture value);

        Sprite(const char* name = "Sprite" + (Sprite::spriteIdCounter + 48),
               unsigned int chunkID = 0,
               glm::vec3 position = glm::vec3(.0f),
               SpriteTexture texture = SpriteTexture(),
               bool updatable = true);
    };
} // namespace ast