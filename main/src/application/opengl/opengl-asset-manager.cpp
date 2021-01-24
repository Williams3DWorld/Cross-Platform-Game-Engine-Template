#include "opengl-asset-manager.hpp"
#include "../../core/utils/TinyXML/tinyxml.h"
#include "../../core/utils/assets.hpp"
#include <unordered_map>




namespace ast
{
    struct OpenGLAssetManager::Internal
    {
        std::unordered_map<std::string, ast::OpenGLPipeline> pipelineCache;
        std::unordered_map<int, ast::OpenGLTexture> textureCache;
        std::unordered_map<std::string, ast::TiledMap> mapCache;

        Internal() {}

        void loadPipelines()
        {
            pipelineCache.insert(std::make_pair(
                "default",
                ast::OpenGLPipeline("default")));
        }

        void loadTexture(const std::string source, int id)
        {
            textureCache.insert(std::pair(
                id,
                ast::OpenGLTexture(ast::assets::loadBitmap(source))));
        }

        void loadTiledMap(std::string map)
        {
            mapCache.clear();
            ast::TiledMap newMap = ast::MapParser::GetInstance()->parse(map);
            mapCache.insert(std::make_pair(map, newMap));
        }
    };

    OpenGLAssetManager::OpenGLAssetManager() : internal(ast::make_internal_ptr<Internal>()) {}

    void ast::OpenGLAssetManager::loadAssetsFromFile(const char* fileURI)
    {
        TiXmlDocument* xml_document = new TiXmlDocument("assets/assets.xml");
        auto loadValid = xml_document->LoadFile();

        if (!loadValid)
        {
            std::cerr << "Error: Invalid xml file!\n";
            return;
        }

        auto root = xml_document->RootElement();

        for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("textures"))
            {
                for (TiXmlElement* e2 = e->FirstChildElement(); e2 != nullptr; e2 = e2->NextSiblingElement())
                {
                    int id = 0;
                    std::string source = "";

                    e2->Attribute("id", &id);
                    e2->QueryStringAttribute("source", &source);

                    this->internal->loadTexture(source, id);
                }
            }
        }
    }

    void OpenGLAssetManager::loadPipelines()
    {
        internal->loadPipelines();
    }

    void OpenGLAssetManager::loadTextures(const std::string source, int id)
    {
        internal->loadTexture(source, id);
    }

    void ast::OpenGLAssetManager::loadTiledMap(const std::string map)
    {
        internal->loadTiledMap(map);
    }

    const ast::TiledMap& ast::OpenGLAssetManager::getTiledMap(std::string map) const
    {
        return internal->mapCache.at(map);
    }

    const ast::OpenGLTexture& OpenGLAssetManager::getTexture(int id) const
    {
        return internal->textureCache.at(id);
    }

    const ast::OpenGLPipeline& OpenGLAssetManager::getPipeline()
    {
        return internal->pipelineCache.at("default");
    }

    OpenGLAssetManager& ast::OpenGLAssetManager::get()
    {
        static OpenGLAssetManager instance;
        return instance;
    }
} // namespace ast