#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "../../utils/internal-ptr.hpp"
#include "../../utils/TinyXML/tinyxml.h"
#include "tiled-map.hpp"


namespace ast
{
    struct MapParser
    {
        MapParser();

        static MapParser* GetInstance() {
            if (!instance) {
                instance = new MapParser();
            }

            return instance;
        }

        ast::TiledMap parse(std::string file);
        std::vector<unsigned int> MapParser::getLayerTileData(TiXmlElement* root, unsigned int width, unsigned int height);
        std::vector<ast::Tileset> parseTilesetData(std::map<int, std::string>& tilesets);

        std::vector<ast::TiledLayer> separateMultiTextureLayers(ast::TiledMap& map, std::vector<ast::Tileset>& tilesets);

    private:
        static MapParser* instance;

        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
}
