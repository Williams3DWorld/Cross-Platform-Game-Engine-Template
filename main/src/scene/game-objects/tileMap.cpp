#include "tileMap.hpp"
#include "../../core/utils/assets.hpp"
#include "../../global/player-settings.hpp"
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

    std::unique_ptr<ast::Player>& TileMap::getPlayer() {
        return this->player;
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
    void TileMap::render(unsigned int matrix_location, glm::mat4 camera_matrix)
    {
        for (auto const& layer : this->layers)
        {
            layer.second->render();
        }
        
        this->player->render(static_cast<unsigned int>(matrix_location), camera_matrix);
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

        this->player = std::make_unique<ast::Player>(glm::vec3(
            0.f,
            0.f,
            PLAYER_RADIUS));
    }
} // namespace ast