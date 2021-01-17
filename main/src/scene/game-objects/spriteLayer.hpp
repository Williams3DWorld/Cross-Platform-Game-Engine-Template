#ifndef __SPRITE_LAYER_H__
#define __SPRITE_LAYER_H__

#include "../../application/opengl/opengl-batch.hpp"
#include "layer.hpp"

namespace ast
{
    class SpriteLayer : public Layer
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
        virtual void render(unsigned int matrix_location = 0, glm::mat4 camera_matrix = glm::mat4(1.f)) override;

        SpriteLayer(const char* name, unsigned int id, glm::vec3 position,
                    unsigned int textureID = 0,
                    bool updatable = true);
    };
} // namespace ast

#endif