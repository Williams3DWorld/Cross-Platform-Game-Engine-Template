#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "opengl-asset-manager.hpp"
#include <memory>

namespace ast
{
    struct OpenGLRenderer
    {
    public:
        OpenGLRenderer() {}

        void render(ast::OrthoCamera2D& camera, ast::TileMap& map);
    };
} // namespace ast
