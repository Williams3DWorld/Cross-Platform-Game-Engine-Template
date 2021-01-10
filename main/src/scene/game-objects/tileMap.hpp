#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include "layer.hpp"
#include <map>

namespace ast
{
    class TileMap : public TransformObject
    {
    private:
        unsigned int width;
        unsigned int height;

        std::map<unsigned int, std::shared_ptr<ast::Layer>> layers;

    public:
        unsigned int& getWidth();
        unsigned int& getHeight();
        std::map<unsigned int, std::shared_ptr<ast::Layer>> &getLayers();

        void setWidth(unsigned int value);
        void setHeight(unsigned int value);
        void setLayerData(std::map<unsigned int, std::shared_ptr<ast::Layer>> &value);

        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value) override {}
        virtual void update(float dt) override;
        virtual void render() override;

        TileMap();
        TileMap(unsigned int width, unsigned int height, std::map<unsigned int, std::shared_ptr<ast::Layer>> &layers);
    };
} // namespace ast

#endif