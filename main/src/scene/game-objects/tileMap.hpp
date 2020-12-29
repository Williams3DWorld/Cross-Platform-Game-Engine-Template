#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include "sprite.hpp"
#include <map>

namespace ast
{
    class TileMap : public TransformObject
    {
    private:
        unsigned int width;
        unsigned int height;

        std::map<unsigned int, ast::Sprite> chunkData;
        bool chunkCullable(unsigned int chunkIndex);

    public:
        unsigned int& getWidth();
        unsigned int& getHeight();
        std::map<unsigned int, ast::Sprite>& getChunkData();

        void setWidth(unsigned int value);
        void setHeight(unsigned int value);
        void setChunkData(std::map<unsigned int, Sprite>& value);

        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value) override {}
        virtual void update(float dt) override {}

        void render();

        TileMap();
        TileMap(unsigned int width, unsigned int height, std::map<unsigned int, Sprite>& chunkData);
    };
} // namespace ast

#endif