#include "opengl-application.hpp"
#include "../../core/utils/glm-wrapper.hpp"
#include "../../core/utils/log.hpp"
#include "../../core/utils/sdl-wrapper.hpp"
#include "../../scene/scene-main.hpp"


using ast::OpenGLApplication;

namespace
{
    enum SwapIntervalTypes
    {
        ADAPTIVE_VSYNC = -1,
        IMMEDIATE = 0,
        VSYNC = 1
    };

    SDL_GLContext createContext(SDL_Window* window)
    {
        static const std::string logTag{"ast::OpenGLApplication::createContext"};

        SDL_GLContext context{SDL_GL_CreateContext(window)};

#ifdef WIN32
        glewInit();
#endif

        int viewportWidth;
        int viewportHeight;
        SDL_GL_GetDrawableSize(window, &viewportWidth, &viewportHeight);
        SDL_GL_SetSwapInterval(IMMEDIATE);
        SDL_GL_MakeCurrent(window, context);
        ast::log(logTag, "Created OpenGL context with viewport size: " + std::to_string(viewportWidth) + " x " + std::to_string(viewportHeight));

        glClearDepthf(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glViewport(0, 0, viewportWidth, viewportHeight);

        return context;
    }

    std::shared_ptr<ast::OpenGLAssetManager> createAssetManager()
    {
        return std::make_shared<ast::OpenGLAssetManager>(ast::OpenGLAssetManager());
    }

    ast::OpenGLRenderer createRenderer(std::shared_ptr<ast::OpenGLAssetManager> assetManager)
    {
        return ast::OpenGLRenderer(assetManager);
    }

    std::unique_ptr<ast::SceneMain> createMainScene(ast::OpenGLAssetManager& assetManager)
    {
        std::pair<uint32_t, uint32_t> displaySize{ast::sdl::getDisplaySize()};
        std::unique_ptr<ast::SceneMain> scene{std::make_unique<ast::SceneMain>(
            static_cast<float>(displaySize.first),
            static_cast<float>(displaySize.second))};
        scene->prepare(assetManager);
        return scene;
    }
} // namespace

struct OpenGLApplication::Internal
{
    SDL_Window* window;
    SDL_GLContext context;
    const std::shared_ptr<ast::OpenGLAssetManager> assetManager;
    ast::OpenGLRenderer renderer;
    std::unique_ptr<ast::SceneMain> scene;

    Internal() : window(ast::sdl::createWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)),
                 context(::createContext(window)),
                 assetManager(::createAssetManager()),
                 renderer(::createRenderer(assetManager)){
    }

    ast::SceneMain& getScene()
    {
        if (!scene)
        {
            scene = ::createMainScene(*assetManager);
        }

        return *scene;
    }

    void update(const float& delta)
    {
        getScene().update(delta);
    }

    void render()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        getScene().render(renderer);

        SDL_GL_SwapWindow(window);
    }

    ~Internal()
    {
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
    }
};

OpenGLApplication::OpenGLApplication() : internal(ast::make_internal_ptr<Internal>()) {}

void OpenGLApplication::update(const float& delta)
{
    internal->update(delta);
}

void OpenGLApplication::render()
{
    internal->render();
}
