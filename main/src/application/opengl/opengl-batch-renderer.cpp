#include "opengl-batch-renderer.hpp"
#include "../../core/renderer/sprite-vertex.hpp"
#include <GL/glew.h>
#include <map>

namespace ast
{
    struct OpenGLBatchRenderer::Internal
    {
        SpriteBatch batch;

        // TODO: Use pre-loaded sprite data instead of using the GameObjectPool
        void compileData(std::vector<std::map<unsigned int, ast::Sprite>>& layers)
        {
            for (auto object : GameObjectPool::gameObjects)
            {
                auto offsetCount = 0;
                if (object.second->getType() == SPRITE)
                {
                    const std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(object.second);
                    const auto spriteID = sprite->getSpriteID();
                    const auto position = sprite->getPosition();
                    const auto tileID = sprite->getTileID();
                    const auto textureID = sprite->getTextureID();

                    const SpriteVertex spriteVertex = SpriteVertex(position, textureID, tileID, glm::vec2(TILE_SIZE));

                    for (auto vertexFloatValue : spriteVertex.vertexData)
                        this->batch.vertexData.emplace_back(vertexFloatValue);
                    for (auto indexValue : spriteVertex.indexData)
                    {
                        unsigned int indexOffset = indexValue + RECT_VERTEX_COUNT * static_cast<unsigned int>(batch.offsetData.size());
                        this->batch.indexData.emplace_back(indexOffset);
                    }

                    this->batch.offsetData[spriteID] = offsetCount;
                    offsetCount++;
                }
            }
        }

        void createBuffers()
        {
            // VAO
            glGenVertexArrays(1, &batch.vao);
            glBindVertexArray(batch.vao);

            // VBO
            glGenBuffers(1, &this->batch.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, batch.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->batch.vertexData.size(), this->batch.vertexData.data(), GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);   // POSITIONS
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);   // TEXCOORDS
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);   // TEXTURE ID
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
            glEnableVertexAttribArray(3); // TILE ID
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));

            // IBO
            glGenBuffers(1, &this->batch.ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * this->batch.indexData.size(), this->batch.indexData.data(), GL_DYNAMIC_DRAW);
        }

        Internal()
        {
            std::vector<std::map<unsigned int, ast::Sprite>> tempData = {};
            this->compileData(tempData);
            this->createBuffers();
        }

        ~Internal()
        {
            glDeleteBuffers(1, &this->batch.vbo);
            glDeleteBuffers(1, &this->batch.ibo);
            glDeleteVertexArrays(1, &this->batch.vao);
        }
    };

    void OpenGLBatchRenderer::render()
    {
        // Bind uniform textures here..?
        glBindVertexArray(internal->batch.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, internal->batch.ibo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(internal->batch.indexData.size()), GL_UNSIGNED_INT, 0);
    }

    OpenGLBatchRenderer::OpenGLBatchRenderer() : internal(ast::make_internal_ptr<Internal>()) {}
} // namespace ast