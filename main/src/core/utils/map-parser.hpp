#pragma once

#include <iostream>
#include <map>

#include "../utils/internal-ptr.hpp"
#include "../utils/TinyXML/tinyxml.h"

namespace ast
{
    struct MapParser
    {
        MapParser();

        void parse(const char* file);
        void parseLayer(TiXmlElement* element, int layerID, int rowcount, int colcount);
    private:
        std::map<int, int**> gameLayers; 

        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
}