#include <array>
#include "../../global/tile-settings.hpp"

#define RECT_VERTEX_COUNT 4
#define RECT_INDEX_COUNT 6

namespace ast
{
    struct CharacterVertex
    {
        std::array<float, 24> vertexData;
        std::array<unsigned int, 6> indexData;

        CharacterVertex(glm::vec2 position = {.0f, .0f},
                      glm ::vec2 size = glm::vec2(64.f), float tileID = 0)
        {
            this->vertexData = {
                position.x, position.y, .0f, .0f, .0f, tileID,
                position.x + size.x, position.y, .0f, 1.f, .0f, tileID,
                position.x + size.x, position.y + size.y, .0f, 1.f, 1.f, tileID,
                position.x, position.y + size.y, .0f, 0.f, 1.f, tileID};

            this->indexData = {0, 1, 2, 2, 3, 0};
        }
    };

} // namespace ast