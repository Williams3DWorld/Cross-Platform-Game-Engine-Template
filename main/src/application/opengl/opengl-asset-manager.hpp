#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "opengl-pipeline.hpp"
#include "opengl-texture.hpp"

namespace ast
{
    struct OpenGLAssetManager
    {
        OpenGLAssetManager();

        void loadPipelines();
        void loadTextures(const std::vector<std::string> textures);
        const ast::OpenGLTexture& getTexture(std::string& texture) const;
        const ast::OpenGLPipeline& getPipeline();

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
