#pragma once

#include "../core/utils/internal-ptr.hpp"
#include "../application/opengl/opengl-asset-manager.hpp"
#include "../application/opengl/opengl-renderer.hpp"

namespace ast
{
    struct SceneMain
    {
        SceneMain(const float& screenWidth, const float& screenHeight);

        void prepare(ast::OpenGLAssetManager& assetManager);

        void update(const float& delta);

        void render(ast::OpenGLRenderer& renderer);

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
