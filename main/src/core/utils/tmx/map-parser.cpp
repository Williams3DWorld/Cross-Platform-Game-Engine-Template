#include "map-parser.hpp"
#include <algorithm>

using ast::MapParser;

/*
* Internal structure for xml reading and writing helper functions
*/
struct MapParser::Internal
{
    TiXmlDocument* xml_document;

    void loadXML(const std::string& file)
    {
        xml_document = new TiXmlDocument(file);
        bool loadValid = xml_document->LoadFile();

        if (loadValid)
            printf("ast::MapParser::loadXML: Successfully loaded XML File\n");
        else
            printf("ast::MapParser::loadXML: Failed to load XML File\n");
    }

    TiXmlDocument* GetXmlDocument()
    {
        return xml_document;
    }
};

MapParser* MapParser::instance;

/*
* Constructer
*/
MapParser::MapParser() : internal(ast::make_internal_ptr<Internal>()) {}

/*
* Parse XML map data
*/
ast::TiledMap MapParser::parse(std::string file)
{
    TiledMap tiledMap("undefined", {});

    internal->loadXML("assets/maps/" + file);
    TiXmlElement* root = internal->GetXmlDocument()->RootElement();
    TiXmlElement* settings = root->FirstChildElement();

    std::string fileName = "";
    settings->FirstChildElement()->NextSiblingElement()->QueryStringAttribute("target", &fileName);
    tiledMap.name = fileName.replace(fileName.size() - 4, 4, "").c_str();

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        int layerID = 0;
        int width = 0;
        int height = 0;

        if (e->Value() == std::string("layer"))
        {
            int id = 0;
            int width = 0;
            int height = 0;

            e->Attribute("id", &id);
            e->Attribute("width", &width);
            e->Attribute("height", &height);

            tiledMap.layers.emplace_back(ast::TiledLayer(static_cast<unsigned int>(id), static_cast<unsigned int>(width), static_cast<unsigned int>(height), {}));
            tiledMap.layers[tiledMap.layers.size() - 1].tileIDs = this->getLayerTileData(e, width, height);
        }
        else if (e->Value() == std::string("tileset"))
        {
            int firstgid = 0;
            std::string source = "";
            e->Attribute("firstgid", &firstgid);
            e->QueryStringAttribute("source", &source);
            tiledMap.tilesets.insert(std::make_pair(firstgid - 1, source));
        }
    }

    std::sort(
        tiledMap.layers.begin(), tiledMap.layers.end(), [](ast::TiledLayer& a, ast::TiledLayer& b) { return a.id > b.id; });

    auto tilesets = this->parseTilesetData(tiledMap.tilesets);
    tiledMap.layers = this->separateMultiTextureLayers(tiledMap, tilesets);

    delete root;

    return tiledMap;
}

std::vector<unsigned int> MapParser::getLayerTileData(TiXmlElement* root, unsigned int width, unsigned int height)
{
    std::vector<unsigned int> layerData;
    TiXmlElement* layerElement;
    std::string tile_matrix = "";

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("data"))
        {
            layerElement = e;
            tile_matrix = layerElement->GetText();
            break;
        }
    }

    std::istringstream iss(tile_matrix);
    std::string id;

    size_t mapSize = static_cast<size_t>(width * height);
    layerData.resize(mapSize);

    for (auto i = 0; i < mapSize; i++)
    {
        std::getline(iss, id, ',');
        std::stringstream convertor(id);
        convertor >> layerData[i];

        if (!iss.good())
            break;
    }

    return layerData;
}

std::vector<ast::Tileset> ast::MapParser::parseTilesetData(std::map<int, std::string>& tilesets)
{
    std::vector<ast::Tileset> res;

    for (auto const& tileset : tilesets)
    {
        TiledMap tiledMap("undefined", {});
        internal->loadXML("assets/maps/" + tileset.second);

        TiXmlElement* root = internal->GetXmlDocument()->RootElement();
        TiXmlElement* image = root->FirstChildElement();

        int width = 0;
        int height = 0;
        int columns = 0;
        int tileSize = 0;
        int tileCount = 0;
        std::string name = "";
        std::string source = "";
        
        root->QueryStringAttribute("name", &name);
        root->Attribute("tilewidth", &tileSize);
        root->Attribute("tilecount", &tileCount);
        root->Attribute("columns", &columns);

        image->QueryStringAttribute("source", &source);
        image->Attribute("width", &width);
        image->Attribute("height", &height);

        res.emplace_back(ast::Tileset(name, source, width, height, columns, tileSize, tileCount));

        delete root;
    }

    return res;
}

std::vector<ast::TiledLayer> ast::MapParser::separateMultiTextureLayers(ast::TiledMap& map, std::vector<ast::Tileset>& tilesets)
{
    std::vector<TiledLayer> res;
    if (map.tilesets.size() < 2)
        return map.layers;

    const int startLayerID = map.layers[map.layers.size() - 1].id;

    for (auto i = 0; i < map.layers.size(); ++i)
    {
        for (auto j = 0; j < map.layers[i].tileIDs.size(); ++j)
        {
            // Compare each tileID with each tileset threshold and add new layers for each unique texture
            for (auto k = 0; k < tilesets.size(); ++k)
            {
                
            }   
        }
    }

    return res;
}