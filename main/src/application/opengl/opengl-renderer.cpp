#include "opengl-renderer.hpp"

using ast::OpenGLRenderer;

struct OpenGLRenderer::Internal
{
    const std::shared_ptr<ast::OpenGLAssetManager> assetManager;

    Internal(std::shared_ptr<ast::OpenGLAssetManager> assetManager) : assetManager(assetManager) {}

    void render(
        const ast::assets::Pipeline& pipeline, ast::OrthoCamera2D& camera)
    {
        assetManager->getPipeline(pipeline).render(camera);
    }
};

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<ast::OpenGLAssetManager> assetManager)
    : internal(ast::make_internal_ptr<Internal>(assetManager)) {}

void OpenGLRenderer::render(
    const ast::assets::Pipeline& pipeline, ast::OrthoCamera2D& camera)
{
    internal->render(pipeline, camera);
}
