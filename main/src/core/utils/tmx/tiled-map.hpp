#ifndef __TILED_MAP_H__
#define __TILED_MAP_H__

#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace ast
{
    struct Tileset
    {
        int width;
        int height;
        int columns;
        int tileSize;
        int tileCount;
        std::string name;
        std::string source;

        Tileset(std::string name, std::string source, int width, int height, int columns, int tileSize, int tileCount) {
            this->name = name;
            this->source = source;
            this->width = width;
            this->height = height;
            this->columns = columns;
            this->tileSize = tileSize;
            this->tileCount = tileCount;
        }
    };

    struct TiledLayer
    {
        unsigned int id;
        unsigned int width;
        unsigned int height;
        unsigned int texID;

        std::vector<unsigned int> tileIDs;

        TiledLayer(unsigned int id, unsigned int width, unsigned int height, unsigned int texID, std::vector<unsigned int> tileIDs) : id(id), width(width), height(height), tileIDs(tileIDs), texID(texID) {}
    };

    struct TiledObject 
    {
        int id;
        glm::vec2 position;
        glm::vec2 scale;

        TiledObject(int& id, const glm::vec2& position, const glm::vec2& scale)
            : id(id), position(position), scale(scale) {}
    };

    struct TiledObjectGroup
    {
        unsigned int id;
        std::string name;
        std::vector<TiledObject> tiledObjects;

        TiledObjectGroup(unsigned int id, const std::string& name) : name(name), id(id) {}
    };

    struct TiledMap
    {
        const char* name;
        std::vector<TiledLayer> layers;
        std::vector<TiledObjectGroup> objectLayers;
        std::map<int, std::string> tilesets;

        TiledMap(const char* name, std::vector<TiledLayer> layers) : name(name), layers(layers) {}
    };
}

#endif