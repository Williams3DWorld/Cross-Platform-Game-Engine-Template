#include "../../scene/game-objects/sprite.hpp"
#include <array>

#define NUM_ATTRIBS 3
#define VERTEX_STRIDE 8

/* [ x, y, z, uOffset, vOffset, uScale, vScale, textureID ] */

namespace ast
{

    struct SpriteBatch
    {
        unsigned int vao;
        unsigned int vbo;
        unsigned int ibo;

        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;
        std::unordered_map<unsigned int, unsigned int> offsetData;

        void updateSubData(unsigned int spriteID, float data[])
        {
            auto vertex = 0;
            for (auto i = spriteID * VERTEX_STRIDE; i < VERTEX_STRIDE; i++)
            {
                this->vertexData[i] = data[vertex];
                vertex++;
            }
        }

        SpriteBatch() : vbo(0), vao(0), ibo(0) {}
    };

    class OpenGLSpriteRenderer
    {
    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;

    public:
        void render();

        OpenGLSpriteRenderer();
    };
} // namespace ast