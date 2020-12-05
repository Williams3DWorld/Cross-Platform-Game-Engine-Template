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

        Sprite(const char* name, unsigned int chunkID, glm::vec3 position, SpriteTexture texture, bool updatable);
    };
} // namespace ast