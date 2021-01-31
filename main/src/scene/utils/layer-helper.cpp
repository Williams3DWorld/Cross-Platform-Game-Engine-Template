#include "layer-helper.hpp"
#include "../../core/renderer/sprite-vertex.hpp"
#include <iostream>
#include <string>

namespace ast
{
    std::vector<ast::CollisionRectangle> LayerHelper::createCollisionDataFromTiledLayer(ast::TiledMap& tilemap)
    {
        std::vector<ast::CollisionRectangle> res;
 
        for (auto i = 0; i < tilemap.objectLayers.size(); i++)
        {
            const auto objectGroup = tilemap.objectLayers[i];

            if (objectGroup.name == "Collisions")
            {
                for (auto const& object : objectGroup.tiledObjects) {
                    res.emplace_back(ast::CollisionRectangle(
                        static_cast<int>(object.position.x), 
                        static_cast<int>(object.position.y),
                        static_cast<int>(object.scale.x),
                        static_cast<int>(object.scale.y)));
                }
            }
        }

        return res;
    }

    std::shared_ptr<ast::SpriteLayer> LayerHelper::createSpriteLayerFromTiledLayer(ast::TiledLayer& tilelayer)
    {
        auto res = std::make_shared<ast::SpriteLayer>("layer", tilelayer.id, glm::vec3(.0f), tilelayer.texID, true);

        std::cout << "id: " << tilelayer.id << "\n";

        std::vector<float> vertexData;;
        std::vector<unsigned int> indexData;
        auto offset = glm::vec3(.0f);
        auto numSprites = 0;
        for (auto i = 0; i < tilelayer.tileIDs.size(); i++)
        {
            auto tileID = tilelayer.tileIDs[i];

            if (tileID == 0)
                continue;

            offset = glm::vec3(static_cast<float>(i % tilelayer.width) * TILE_SIZE * TILE_SCALE,
                               static_cast<float>(floor(i / tilelayer.width)) * TILE_SIZE * TILE_SCALE, .0f);

            auto sprite = std::make_shared<Sprite>();

            sprite->setPosition(offset);
            sprite->setTileID(static_cast<float>(tileID - 1));

            res->addChild(std::static_pointer_cast<GameObject>(sprite));

            const SpriteVertex spriteVertex = SpriteVertex(offset, 0, static_cast<float>(tileID - 1), glm::vec2(TILE_SIZE));

            for (auto vertexFloatValue : spriteVertex.vertexData)
                vertexData.emplace_back(vertexFloatValue);

            for (auto indexValue : spriteVertex.indexData)
            {
                unsigned int indexOffset = indexValue + RECT_VERTEX_COUNT * numSprites;
                indexData.emplace_back(indexOffset);
            }

            numSprites++;
        }

        res->setBufferData(vertexData, indexData);

        return res;
    }

    std::vector<std::shared_ptr<ast::SpriteLayer>> LayerHelper::createSpriteLayersFromTiledMap(ast::TiledMap& tilemap)
    {
        std::vector<std::shared_ptr<ast::SpriteLayer>> res;

        for (auto i = 0; i < tilemap.layers.size(); i++)
        {
            auto tiledLayer = tilemap.layers[i];
            auto layer = ast::LayerHelper::createSpriteLayerFromTiledLayer(tiledLayer);
            res.emplace_back(layer);
        }

        return res;
    }
} // namespace ast