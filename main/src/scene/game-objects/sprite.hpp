#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "transformObject.hpp"

namespace ast
{
    class Sprite : public TransformObject
    {
    private:
        static unsigned int spriteIdCounter;

    protected:
        float _tileID;
        float _textureID;
        unsigned int _spriteID;
        unsigned int _chunkID;

    public:
        float& getTileID();
        float& getTextureID();
        unsigned int& getSpriteID();
        unsigned int& getChunkID();

        void setChunkID(unsigned int value);
        void setTextureID(float value);
        void setTileID(float value);

        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value) override {}
        virtual void update(float dt) override {}
        virtual void render() override{}

        Sprite(const char* name = "Sprite" + (Sprite::spriteIdCounter + 48),
               glm::vec3 position = glm::vec3(.0f),
               float textureID = 0,
               float tileID = 0, 
               unsigned int chunkID = 0,
               bool updatable = true);
    };
} // namespace ast

#endif