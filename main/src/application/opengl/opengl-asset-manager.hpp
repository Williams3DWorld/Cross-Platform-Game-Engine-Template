#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "opengl-pipeline.hpp"
#include "opengl-texture.hpp"
#include "../../core/utils/tmx/map-parser.hpp"

namespace ast
{
    class OpenGLAssetManager
    {
    public:

        OpenGLAssetManager();
        static OpenGLAssetManager& get();

        void loadAssetsFromFile(const char* fileURI);
        void loadPipelines();
        void loadTextures(const std::string source, int id);
        void loadTiledMap(const std::string map);

        const ast::TiledMap& getTiledMap(std::string map) const;
        const ast::OpenGLTexture& getTexture(int id) const;
        const ast::OpenGLPipeline& getPipeline();


    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
