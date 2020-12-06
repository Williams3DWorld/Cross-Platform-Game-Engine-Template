#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "../../core/renderer/renderer.hpp"
#include "opengl-asset-manager.hpp"
#include <memory>

namespace ast
{
    struct OpenGLRenderer : public ast::Renderer
    {
        OpenGLRenderer(std::shared_ptr<ast::OpenGLAssetManager> assetManager);

        void render(
            const ast::assets::Pipeline& pipeline, ast::OrthoCamera2D& camera) override;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
