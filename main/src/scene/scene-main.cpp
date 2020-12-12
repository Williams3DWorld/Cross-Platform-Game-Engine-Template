#include "scene-main.hpp"
#include "../core/utils/sdl-wrapper.hpp"
#include "player.hpp"
#include "../core/camera/ortho-camera-2d.hpp"

using ast::SceneMain;
using ast::assets::Pipeline;
using ast::assets::StaticMesh;
using ast::assets::Texture;

namespace
{
    ast::OrthoCamera2D createOrthoCamera(const float& width, const float& height)
    {
        return ast::OrthoCamera2D(width, height);
    }
} // namespace

struct SceneMain::Internal
{
    ast::OrthoCamera2D camera;
    ast::Player player;
    const uint8_t* keyboardState;


    Internal(const float& screenWidth, const float& screenHeight)
        : camera(::createOrthoCamera(screenWidth, screenHeight)),
          player(ast::Player(glm::vec3{0.0f, 0.0f, 300.0f})),
          keyboardState(SDL_GetKeyboardState(nullptr)) {}

    void prepare(ast::AssetManager& assetManager)
    {
        assetManager.loadPipelines({Pipeline::Default});
        assetManager.loadTextures({Texture::Crate, Texture::RedCrossHatch});
    }

    void update(const float& delta)
    {
        processInput(delta);

        camera.configure(player.getPosition());
    }

    void render(ast::Renderer& renderer)
    {
        renderer.render(Pipeline::Default, camera);
    }

    void processInput(const float& delta)
    {
        if (keyboardState[SDL_SCANCODE_A])
        {
            player.moveUp(delta);
        }

        if (keyboardState[SDL_SCANCODE_S])
        {
            player.moveDown(delta);
        }

        if (keyboardState[SDL_SCANCODE_A])
        {
            player.moveLeft(delta);
        }

        if (keyboardState[SDL_SCANCODE_D])
        {
            player.moveRight(delta);
        }
    }
};

SceneMain::SceneMain(const float& screenWidth, const float& screenHeight)
    : internal(ast::make_internal_ptr<Internal>(screenWidth, screenHeight)) {}

void SceneMain::prepare(ast::AssetManager& assetManager)
{
    internal->prepare(assetManager);
}

void SceneMain::update(const float& delta)
{
    internal->update(delta);
}

void SceneMain::render(ast::Renderer& renderer)
{
    internal->render(renderer);
}
