#include <array>

#define RECT_VERTEX_COUNT 4
#define RECT_INDEX_COUNT 6

namespace ast
{
    struct SpriteVertex
    {
        std::array<float, 28> vertexData;
        std::array<unsigned int, 6> indexData;

        SpriteVertex(glm::vec3 position = {.0f, .0f, .0f}, float textureID = 0, float tileID = 0, glm ::vec2 size = glm::vec2(64.f), glm::vec3 scale = {1.f, 1.f, 1.f})
        {
            this->vertexData = {
                position.x, position.y, .0f,                        .0f, .0f,   textureID,  tileID,
                position.x + size.x, position.y, .0f,               1.f, .0f,   textureID,  tileID,
                position.x + size.x, position.y + size.y, .0f,      1.f, 1.f,   textureID,  tileID,
                position.x, position.y + size.y, .0f,               0.f, 1.f,   textureID,  tileID
            };

            this->indexData = {0, 1, 2, 2, 3, 0};
        }
    };
} // namespace ast