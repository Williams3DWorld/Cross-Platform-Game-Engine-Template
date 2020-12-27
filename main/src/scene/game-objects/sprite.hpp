#include "TransformObject.hpp"

namespace ast
{
    class Sprite : public TransformObject
    {
    private:
        static unsigned int spriteIdCounter;

    protected:
        bool _visible;
        float _tileID;
        float _textureID;
        unsigned int _spriteID;
        unsigned int _chunkID;

    public:
        bool& getVisible();
        float& getTileID();
        float& getTextureID();
        unsigned int& getSpriteID();
        unsigned int& getChunkID();

        void setVisible(bool value);
        void setChunkID(unsigned int value);
        void setTextureID(float value);
        void setTileID(float value);

        Sprite(const char* name = "Sprite" + (Sprite::spriteIdCounter + 48),
               glm::vec3 position = glm::vec3(.0f),
               float textureID = 0,
               float tileID = 0, 
               unsigned int chunkID = 0,
               bool updatable = true);
    };
} // namespace ast