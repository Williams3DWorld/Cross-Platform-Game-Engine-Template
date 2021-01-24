#include "opengl-application.hpp"
#include "../../core/utils/glm-wrapper.hpp"
#include "../../core/utils/log.hpp"
#include "../../core/utils/sdl-wrapper.hpp"
#include "../../game.hpp"


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

    ast::OpenGLRenderer createRenderer()
    {
        return ast::OpenGLRenderer();
    }

    std::unique_ptr<ast::Game> createGame()
    {
        std::pair<uint32_t, uint32_t> displaySize{ast::sdl::getDisplaySize()};
        auto screenWidth = static_cast<float>(displaySize.first);
        auto screenHeight = static_cast<float>(displaySize.second);
        return std::make_unique<ast::Game>(screenWidth, screenHeight);
    }

} // namespace

struct OpenGLApplication::Internal
{
    SDL_Window* window;
    SDL_GLContext context;
    ast::OpenGLRenderer renderer;
    std::unique_ptr<ast::Game> game;

    Internal() : window(ast::sdl::createWindow(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)),
                 context(::createContext(window)),
                 renderer(::createRenderer()),
                 game(::createGame())
                {
    }

    void update(const float& delta)
    {
        game->update(delta);
    }

    void render()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.render(*game->getCamera(), *game->getMap());

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
