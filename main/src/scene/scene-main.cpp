#include "scene-main.hpp"
#include "../core/experimental/perspective-camera.hpp"
#include "../core/experimental/static-mesh-instance.hpp"
#include "../core/utils/sdl-wrapper.hpp"
#include "player.hpp"
#include "../core/camera/ortho-camera-2d.hpp"

using ast::SceneMain;
using ast::assets::Pipeline;
using ast::assets::StaticMesh;
using ast::assets::Texture;

namespace
{
    ast::PerspectiveCamera createPerspectiveCamera(const float& width, const float& height)
    {
        return ast::PerspectiveCamera(width, height);
    }

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

        //const glm::mat4 cameraMatrix{camera.getProjectionMatrix() * camera.getViewMatrix()};


        /*for (auto& staticMesh : staticMeshes)
        {
            staticMesh.rotateBy(delta * 45.0f);
            staticMesh.update(cameraMatrix);
        }*/
    }

    void render(ast::Renderer& renderer)
    {
        renderer.render(Pipeline::Default, camera);
    }

    void processInput(const float& delta)
    {
        if (keyboardState[SDL_SCANCODE_UP])
        {
            player.moveForward(delta);
        }

        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            player.moveBackward(delta);
        }

        if (keyboardState[SDL_SCANCODE_A])
        {
            player.moveUp(delta);
        }

        if (keyboardState[SDL_SCANCODE_Z])
        {
            player.moveDown(delta);
        }

        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            player.turnLeft(delta);
        }

        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            player.turnRight(delta);
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
