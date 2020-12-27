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

        void parse(const char* file);
        void parseLayer(TiXmlElement* element, int layerID, int rowcount, int colcount);
    private:
        std::vector<int> layer;

        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
}