#include <vector>

#define RECT_INDEX_COUNT 6

namespace ast
{
    struct ArbitraryData
    {
    protected:
        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;
    };

    struct RectData : public ArbitraryData
    {
        RectData()
        {
            this->vertexData = {-1.f,
                                1.f,
                                .0f,
                                1.f,
                                .0f,
                                -1.f,
                                -1.f,
                                .0f,
                                .0f,
                                .0f,
                                1.f,
                                -1.f,
                                .0f,
                                1.f,
                                .0f,
                                1.f,
                                1.f,
                                .0f,
                                .0f,
                                0.f};

            this->indexData = {0, 1, 2, 0, 2, 3};
        }
    };
} // namespace ast