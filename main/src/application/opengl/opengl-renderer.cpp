#include "opengl-renderer.hpp"

using ast::OpenGLRenderer;

struct OpenGLRenderer::Internal
{
    const std::shared_ptr<ast::OpenGLAssetManager> assetManager;

    Internal(std::shared_ptr<ast::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

    void render(ast::OrthoCamera2D& camera, ast::TileMap& map)
    {
        assetManager->getPipeline().render(camera, map);
    }
};

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<ast::OpenGLAssetManager> assetManager)
    : internal(ast::make_internal_ptr<Internal>(assetManager)) {}

void OpenGLRenderer::render(ast::OrthoCamera2D& camera, ast::TileMap& map)
{
    internal->render(camera, map);
}
