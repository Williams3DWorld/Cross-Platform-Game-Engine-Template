#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "opengl-pipeline.hpp"
#include "opengl-texture.hpp"
#include "../../core/utils/tmx/map-parser.hpp"

namespace ast
{
    struct OpenGLAssetManager
    {
        OpenGLAssetManager();

        void loadPipelines(ast::OpenGLAssetManager& assetManager);
        void loadTextures(const std::vector<std::string> textures);
        void loadTiledMap(const std::string map);

        const ast::TiledMap& getTiledMap(std::string map) const;
        const ast::OpenGLTexture& getTexture(std::string& texture) const;
        const ast::OpenGLPipeline& getPipeline();

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
