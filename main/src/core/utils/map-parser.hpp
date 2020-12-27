#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "../utils/internal-ptr.hpp"
#include "../utils/TinyXML/tinyxml.h"

namespace ast
{
    struct MapParser
    {
        MapParser();

        std::vector<int> GetLayer()
        {
            return layer;
        }

        int GetMapWidth() {
            return map_width;
        }
        int GetMapHeight() {
            return map_height;
        }

        static MapParser* GetInstance() {
            if (instance == 0) {
                instance = new MapParser();
            }

            return instance;
        }

        void parse(const char* file);
        void parseLayer(TiXmlElement* element, int layerID, int rowcount, int colcount);
    private:
        int map_width;
        int map_height;
        std::vector<int> layer;

        static MapParser* instance;

        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
}
