#include "opengl-asset-manager.hpp"
#include "../../core/utils/assets.hpp"
#include "../../core/utils/map-parser.hpp"
#include <unordered_map>

using ast::OpenGLAssetManager;

struct OpenGLAssetManager::Internal
{
    std::unordered_map<std::string, ast::OpenGLPipeline> pipelineCache;
    std::unordered_map<std::string, ast::OpenGLTexture> textureCache;
    std::unordered_map<std::string, ast::TileMap> mapCache;

    Internal() {}

    void loadPipelines()
    {
        pipelineCache.insert(std::make_pair(
            "default",
            ast::OpenGLPipeline("default")));
    }

    void loadTextures(const std::vector<std::string> textures)
    {
        for (const auto& texture : textures)
        {
            if (textureCache.count(texture) == 0)
            {
                textureCache.insert(std::pair(
                    texture,
                    ast::OpenGLTexture(ast::assets::loadBitmap(texture))));
            }
        }
    }

    void loadTiledMap(std::string map) {
        mapCache.clear();
        auto newMap = ast::MapParser::GetInstance()->parse(map);
        mapCache.insert(std::pair(map, newMap));
    }
};

OpenGLAssetManager::OpenGLAssetManager() : internal(ast::make_internal_ptr<Internal>()) {}

void OpenGLAssetManager::loadPipelines()
{
    internal->loadPipelines();
}

void OpenGLAssetManager::loadTextures(const std::vector<std::string> textures)
{
    internal->loadTextures(textures);
}

void ast::OpenGLAssetManager::loadTiledMap(const std::string& map)
{
}

const ast::OpenGLTexture& OpenGLAssetManager::getTexture(std::string& texture) const
{
    return internal->textureCache.at(texture);
}

const ast::OpenGLPipeline& OpenGLAssetManager::getPipeline() 
{
    return internal->pipelineCache.at("default");
}
