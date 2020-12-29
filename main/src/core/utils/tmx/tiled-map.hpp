#ifndef __TILED_MAP_H__
#define __TILED_MAP_H__

#include <map>
#include <vector>

namespace ast
{
    struct TiledLayer
    {
        unsigned int id;
        unsigned int width;
        unsigned int height;

        std::vector<unsigned int> tileIDs;

        TiledLayer(unsigned int id, unsigned int width, unsigned int height, std::vector<unsigned int> tileIDs) : id(id), width(width), height(height), tileIDs(tileIDs) {}
    };

    struct TiledMap
    {
        const char* name;
        std::vector<TiledLayer> layers;

        TiledMap(const char* name, std::vector<TiledLayer> layers) : name(name), layers(layers) {}
    };
}

#endif