#include "tileMap.hpp"
#include <iostream>


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
    std::map<unsigned int, std::shared_ptr<ast::Layer>> &TileMap::getLayers()
    {
        return this->layers;
    }

    void TileMap::setWidth(unsigned int value)
    {
        this->width = value;
    }

    void TileMap::setHeight(unsigned int value)
    {
        this->height = value;
    }

    void TileMap::setLayerData(std::map<unsigned int, std::shared_ptr<ast::Layer>> &value)
    {
        this->layers = value;
    }

    void TileMap::update(float dt)
    {
        for (auto const& layer : this->layers)
        {
            layer.second->update(dt);
        }
    }
    void TileMap::render()
    {
        for (auto const& layer : this->layers)
        {
            layer.second->render();
        }
    }

    TileMap::TileMap()
    {
        this->width = 0;
        this->height = 0;
    }

    TileMap::TileMap(unsigned int width, unsigned int height, std::map<unsigned int, 
        std::shared_ptr<ast::Layer>>& layers, std::vector<ast::CollisionRectangle> collisionRectangles)
    {
        this->width = width;
        this->height = height;
        this->layers = layers;
        this->collisionRectangles = collisionRectangles;
    }
} // namespace ast