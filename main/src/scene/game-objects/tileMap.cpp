#include "tileMap.hpp"

namespace ast
{
    unsigned int& TileMap::getWidth()
    {
        return this->width;
    }

    unsigned int& TileMap::getHeight()
    {
        return this->height;
    }
    std::map<unsigned int, Sprite>& TileMap::getChunkData()
    {
        return this->chunkData;
    }

    void TileMap::setWidth(unsigned int value)
    {
        this->width = value;
    }

    void TileMap::setHeight(unsigned int value)
    {
        this->height = value;
    }

    void TileMap::setChunkData(std::map<unsigned int, Sprite>& value)
    {
        this->chunkData = value;
    }

    bool TileMap::chunkCullable(unsigned int chunkIndex)
    {
        // Calculate off-screen formula here..
        return false;
    }

    void TileMap::render()
    {
        for (auto i = 0; i < this->chunkData.size(); i++)
        {
            if (!this->chunkCullable(i))
            {
                // Render chunk here..
            }
        }
    }

    TileMap::TileMap()
    {
        this->width = 0;
        this->height = 0;
    }

    TileMap::TileMap(unsigned int width, unsigned int height, std::map<unsigned int, Sprite>& chunkData)
    {
        this->width = width;
        this->height = height;
        this->chunkData = chunkData;
    }
} // namespace ast