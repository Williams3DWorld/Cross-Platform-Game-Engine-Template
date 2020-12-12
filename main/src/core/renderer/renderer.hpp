#pragma once

#include "../../core/utils/asset-inventory.hpp"
#include "../../scene/game-objects/sprite.hpp"
#include "../../core/camera/ortho-camera-2d.hpp"
#include <vector>

namespace ast
{
    struct Renderer
    {
        virtual void render(
            const ast::assets::Pipeline& pipeline, ast::OrthoCamera2D& camera) = 0;
    };
} // namespace ast
