#include "../../scene/game-objects/sprite.hpp"

namespace ast
{
    struct SpriteBufferData
    {
        unsigned int textureID;

        unsigned int transformVbo;
        unsigned int textureVbo;

        unsigned int vao;
        unsigned int vbo;
        unsigned int ibo;

        std::vector<glm::mat4> transformData;
        std::vector<glm::vec4> textureData; // uOffset, vOffset, uScale, vScale

        SpriteBufferData(unsigned int texID) : textureID(0), transformVbo(0), textureVbo(0), vbo(0), vao(0), ibo(0)
        {
            this->textureID = texID;
        }
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