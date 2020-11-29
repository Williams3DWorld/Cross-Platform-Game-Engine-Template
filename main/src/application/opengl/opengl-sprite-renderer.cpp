#include "opengl-sprite-renderer.hpp"
#include "../../core/renderer/arbitrary-data.hpp"
#include <GL/glew.h>

namespace ast
{
    struct OpenGLSpriteRenderer::Internal
    {
        std::vector<SpriteBufferData> bufferData;

        bool textureIdAlreadyExists(unsigned int textureID)
        {
            for (unsigned int i = 0; i < bufferData.size(); i++)
            {
                if (bufferData[i].textureID == textureID)
                    return true;
            }

            return false;
        }

        void compileData()
        {
            std::vector<unsigned int> textureIDs;
            for (auto object : GameObjectPool::gameObjects)
            {
                if (object.second->getType() == SPRITE)
                {
                    const std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(object.second);
                    const unsigned int spriteTextureID = sprite->getTexture().getTextureID();
                    if (!textureIdAlreadyExists(spriteTextureID))
                    {
                        this->bufferData.emplace_back(SpriteBufferData(spriteTextureID));
                    }
                }
            }
        }

        void createBuffers()
        {
            // Get constant vertex and index data for each rect
            const RectData rd = RectData();

            // One instance per unique texture
            for (auto buffer : this->bufferData)
            {
                // Model matrices
                glGenBuffers(1, &buffer.transformVbo);
                glBindBuffer(GL_ARRAY_BUFFER, buffer.transformVbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * buffer.transformData.size(), buffer.transformData.data(), GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // Texture offset & scale data

            }
        }

        Internal()
        {
            this->compileData();
            this->createBuffers();
        }

        ~Internal()
        {
            const auto numBuffers = this->bufferData.size();
            for (unsigned int i = 0; i < numBuffers; i++)
            {
                const auto buffer = this->bufferData[i];

                glDeleteBuffers(1, &buffer.transformVbo);
                glDeleteBuffers(1, &buffer.textureVbo);
                glDeleteBuffers(1, &buffer.vbo);
                glDeleteBuffers(1, &buffer.ibo);
                glDeleteVertexArrays(1, &buffer.vao);
            }
        }
    };

    void OpenGLSpriteRenderer::render()
    {
    }

    OpenGLSpriteRenderer::OpenGLSpriteRenderer() : internal(ast::make_internal_ptr<Internal>()) {}
} // namespace ast