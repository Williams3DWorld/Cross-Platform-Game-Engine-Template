#include "layer-helper.hpp"
#include "../../core/renderer/sprite-vertex.hpp"
#include <string>
#include <iostream>
namespace ast
{
    std::shared_ptr<ast::Layer> LayerHelper::createSpriteLayerFromTiledLayer(ast::TiledLayer& tilelayer)
    {
        // TODO: Assign correct layer name and textureID
        auto res = std::make_shared<ast::Layer>("layer", tilelayer.id, glm::vec3(.0f), 0, true);

        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;

        for (auto i = 0; i < tilelayer.tileIDs.size(); i++)
        {
            auto tileID = tilelayer.tileIDs[i];

            if (tileID == 0)
                continue;

            auto sprite = std::make_shared<Sprite>();
            auto offset = glm::vec3(static_cast<float>(i % tilelayer.width) * TILE_SIZE * TILE_SCALE,
                                    static_cast<float>(floor(i / tilelayer.width)) * TILE_SIZE * TILE_SCALE, .0f);
            sprite->setPosition(offset);
            sprite->setTileID(static_cast<float>(tileID - 1));

            res->addChild(std::static_pointer_cast<GameObject>(sprite));

            const SpriteVertex spriteVertex = SpriteVertex(offset, 0, static_cast<float>(tileID), glm::vec2(TILE_SIZE));

            for (auto vertexFloatValue : spriteVertex.vertexData)
                vertexData.emplace_back(vertexFloatValue);

            for (auto indexValue : spriteVertex.indexData)
            {
                unsigned int indexOffset = indexValue + RECT_VERTEX_COUNT * i;
                indexData.emplace_back(indexOffset);
            }
        }

        res->setBufferData(vertexData, indexData);

        return res;
    }

    std::vector<std::shared_ptr<ast::Layer>> LayerHelper::createSpriteLayersFromTiledMap(ast::TiledMap& tilemap)
    {
        std::vector<std::shared_ptr<ast::Layer>> res;
        for (auto i = 0; i < tilemap.layers.size(); i++)
        {
            auto tiledLayer = tilemap.layers[i];
            auto layer = ast::LayerHelper::createSpriteLayerFromTiledLayer(tiledLayer);
            res.emplace_back(layer);
        }

        return res;
    }

} // namespace ast