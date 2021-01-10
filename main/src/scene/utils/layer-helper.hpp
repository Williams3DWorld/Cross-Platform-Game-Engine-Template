#ifndef __LAYER_HELPER_H__
#define __LAYER_HELPER_H__

#include "../game-objects/layer.hpp"
#include "../../core/utils/tmx/tiled-map.hpp"

namespace ast
{
    class LayerHelper
    {
    public:
        static std::shared_ptr<ast::Layer> createSpriteLayerFromTiledLayer(ast::TiledLayer& tilelayer);
        static std::vector<std::shared_ptr<ast::Layer>> createSpriteLayersFromTiledMap(ast::TiledMap& tilemap);
    };
}

#endif