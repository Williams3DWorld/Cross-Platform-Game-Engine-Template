#include "opengl-asset-manager.hpp"
#include "../../core/utils/assets.hpp"
#include <unordered_map>

using ast::OpenGLAssetManager;

struct OpenGLAssetManager::Internal
{
    std::unordered_map<ast::assets::Pipeline, ast::OpenGLPipeline> pipelineCache;
    std::unordered_map<ast::assets::Texture, ast::OpenGLTexture> textureCache;

    Internal() {}

    void loadPipelines(const std::vector<ast::assets::Pipeline>& pipelines)
    {
        for (const auto& pipeline : pipelines)
        {
            if (pipelineCache.count(pipeline) == 0)
            {
                pipelineCache.insert(std::make_pair(
                    pipeline,
                    ast::OpenGLPipeline(ast::assets::resolvePipelinePath(pipeline))));
            }
        }
    }

    void loadTextures(const std::vector<ast::assets::Texture>& textures)
    {
        for (const auto& texture : textures)
        {
            if (textureCache.count(texture) == 0)
            {
                textureCache.insert(std::pair(
                    texture,
                    ast::OpenGLTexture(ast::assets::loadBitmap(ast::assets::resolveTexturePath(texture)))));
            }
        }
    }
};

OpenGLAssetManager::OpenGLAssetManager() : internal(ast::make_internal_ptr<Internal>()) {}

void OpenGLAssetManager::loadPipelines(const std::vector<ast::assets::Pipeline>& pipelines)
{
    internal->loadPipelines(pipelines);
}

void OpenGLAssetManager::loadTextures(const std::vector<ast::assets::Texture>& textures)
{
    internal->loadTextures(textures);
}

const ast::OpenGLPipeline& OpenGLAssetManager::getPipeline(const ast::assets::Pipeline& pipeline) const
{
    return internal->pipelineCache.at(pipeline);
}

const ast::OpenGLTexture& OpenGLAssetManager::getTexture(const ast::assets::Texture& texture) const
{
    return internal->textureCache.at(texture);
}
