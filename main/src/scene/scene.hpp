#pragma once

#include "../core/asset-manager.hpp"
#include "../core/renderer/renderer.hpp"

namespace ast
{
    struct Scene
    {
        Scene() = default;

        virtual ~Scene() = default;

        virtual void prepare(ast::OpenGLAssetManager& assetManager) = 0;

        virtual void update(const float& delta) = 0;

        virtual void render(ast::OpenGLRenderer& renderer) = 0;
    };
} // namespace ast
