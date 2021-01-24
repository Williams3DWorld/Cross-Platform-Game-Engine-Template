#include "opengl-renderer.hpp"

using ast::OpenGLRenderer;

void OpenGLRenderer::render(ast::OrthoCamera2D& camera, ast::TileMap& map)
{
    OpenGLAssetManager::get().getPipeline().render(camera, map);
}
