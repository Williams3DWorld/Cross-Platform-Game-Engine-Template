#ifndef __SPRITE_LAYER_H__
#define __SPRITE_LAYER_H__

#include "sprite.hpp"

namespace ast
{
    class SpriteLayer : public TransformObject
    {
    private:
        unsigned int textureID;

    public:
        unsigned int& getTextureID();

        void setTextureID(unsigned int value);

        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value);
        virtual void update(float dt) override;
        virtual void render() override;

        SpriteLayer(const char* name, unsigned int id, glm::vec3 position,
                    unsigned int textureID = 0,
                    bool updatable = true);
    };
} // namespace ast

#endif