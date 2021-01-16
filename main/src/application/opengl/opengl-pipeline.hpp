#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "../../core/camera/ortho-camera-2d.hpp"
#include "../../core/utils/graphics-wrapper.hpp"
#include "../../scene/game-objects/tileMap.hpp"
#include <string>
#include <vector>

namespace ast
{
    struct OpenGLAssetManager;

    struct OpenGLPipeline
    {
        OpenGLPipeline(const std::string& shaderName, ast::OpenGLAssetManager& assetManager);

        void render(ast::OrthoCamera2D& camera, ast::TileMap& map) const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
