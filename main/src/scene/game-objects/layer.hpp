#ifndef __SPRITE_LAYER_H__
#define __SPRITE_LAYER_H__

#include "../../application/opengl/opengl-batch.hpp"
#include "sprite.hpp"

namespace ast
{
    class Layer : public TransformObject
    {
    private:
        unsigned int textureID;
        std::shared_ptr<ast::OpenGLBatch> vbo;

    public:
        unsigned int& getTextureID();

        void setTextureID(unsigned int value);
        void setBufferData(std::vector<float>& vertexData, std::vector<unsigned int>& indexData);

        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value);
        virtual void update(float dt) override;
        virtual void render() override;

        Layer(const char* name, unsigned int id, glm::vec3 position,
                    unsigned int textureID = 0,
                    bool updatable = true);
    };
} // namespace ast

#endif