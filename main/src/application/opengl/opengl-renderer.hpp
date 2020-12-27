#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "opengl-asset-manager.hpp"
#include <memory>

namespace ast
{
    struct OpenGLRenderer
    {
        OpenGLRenderer(std::shared_ptr<ast::OpenGLAssetManager> assetManager);

        void render(ast::OrthoCamera2D& camera);

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
