#include <array>

#define RECT_VERTEX_COUNT 4
#define RECT_INDEX_COUNT 6

namespace ast
{
    struct SpriteVertex
    {
        std::array<float, 12> vertexData;
        std::array<unsigned int, 6> indexData;

        SpriteVertex(glm::vec3 position = {.0f, .0f, .0f}, glm::vec2 size = {100.f, 100.f}, glm::vec3 scale = {1.f, 1.f, 1.f}, float rotation = 0, float textureID = 0)
        {
            this->vertexData = {
                position.x,
                position.y,
                .0f,
                position.x + size.x,
                position.y,
                .0f,
                position.x + size.x,
                position.y + size.y,
                .0f,
                position.x,
                position.y + size.y,
                .0f,
            };

            this->indexData = {0, 1, 2, 2, 3, 0};
        }
    };
} // namespace ast