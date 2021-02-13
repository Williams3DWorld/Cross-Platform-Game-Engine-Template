#include "opengl-pipeline.hpp"
#include "../../core/utils/log.hpp"
#include "../../global/tile-settings.hpp"
#include "../../core/audio/audioSystem.hpp"
#include "../../../src/core/renderer/textrenderer.hpp"
#include "../../core/gui/button.hpp"
#include <stdexcept>
#include <vector>

using ast::OpenGLPipeline;

namespace
{
    GLuint compileShader(const GLenum& shaderType, const std::string& shaderSource)
    {
        const std::string logTag{"ast::OpenGLPipeline::compileShader"};
        GLuint shaderId{glCreateShader(shaderType)};

        const char* shaderData{shaderSource.c_str()};
        glShaderSource(shaderId, 1, &shaderData, nullptr);
        glCompileShader(shaderId);

        GLint shaderCompilationResult;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompilationResult);

        if (!shaderCompilationResult)
        {
            GLint errorMessageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetShaderInfoLog(shaderId, errorMessageLength, nullptr, &errorMessage[0]);
            ast::log(logTag, &errorMessage[0]);
            throw std::runtime_error(logTag + "Shader failed to compile.");
        }

        return shaderId;
    }

    GLuint createShaderProgram(const std::string& shaderName)
    {
        const std::string logTag{"ast::OpenGLPipeline::createShaderProgram"};

        ast::log(logTag, "Creating pipeline for '" + shaderName + "'");

        const std::string vertexShaderCode{ast::assets::loadTextFile("assets/shaders/opengl/" + shaderName + ".vert")};
        const std::string fragmentShaderCode{ast::assets::loadTextFile("assets/shaders/opengl/" + shaderName + ".frag")};

#ifdef USING_GLES
        std::string vertexShaderSource{"#version 100\n" + vertexShaderCode};
        std::string fragmentShaderSource{"#version 100\nprecision mediump float;\n" + fragmentShaderCode};
#else
        std::string vertexShaderSource{"#version 120\n" + vertexShaderCode};
        std::string fragmentShaderSource{"#version 120\n" + fragmentShaderCode};
#endif

        GLuint shaderProgramId{glCreateProgram()};
        GLuint vertexShaderId{::compileShader(GL_VERTEX_SHADER, vertexShaderSource)};
        GLuint fragmentShaderId{::compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource)};

        glAttachShader(shaderProgramId, vertexShaderId);
        glAttachShader(shaderProgramId, fragmentShaderId);
        glLinkProgram(shaderProgramId);

        GLint shaderProgramLinkResult;
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderProgramLinkResult);

        if (!shaderProgramLinkResult)
        {
            GLint errorMessageLength;
            glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &errorMessageLength);
            std::vector<char> errorMessage(errorMessageLength + 1);
            glGetProgramInfoLog(shaderProgramId, errorMessageLength, nullptr, &errorMessage[0]);
            ast::log(logTag, &errorMessage[0]);
            throw std::runtime_error(logTag + "Shader program failed to compile.");
        }

        glDetachShader(shaderProgramId, vertexShaderId);
        glDetachShader(shaderProgramId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return shaderProgramId;
    }
} // namespace

struct OpenGLPipeline::Internal
{
    const GLuint shaderProgramId;
    const GLuint uniformLocationMVP;
    const GLuint uniformLocationTexture;

    const GLuint guiShaderProgramId;
    const GLuint guiUniformLocationProjection;

    // TODO: Move map into a world class
    std::unique_ptr<ast::TileMap> map;

    // gui testing
    std::unique_ptr<ast::Button> testButton;
    //

    Internal(const std::string& shaderName)
        : shaderProgramId(::createShaderProgram(shaderName)),
          guiShaderProgramId(::createShaderProgram("text")),
          uniformLocationMVP(glGetUniformLocation(shaderProgramId, "u_mvp")),
          uniformLocationTexture(glGetUniformLocation(shaderProgramId, "u_texture")),
          guiUniformLocationProjection(glGetUniformLocation(guiShaderProgramId, "projection"))
    {
        glUniform1i(uniformLocationTexture, 0);

        // lets play some music :)
        AudioSystem::GetInstance()->Initialise();
        AudioSystem::GetInstance()->addSound("bgm", "assets/sounds/bgm.wav", AudioTypes::MUSIC);
        AudioSystem::GetInstance()->Play("bgm", -1);
        //

        // test quad for GUI
        this->testButton = std::make_unique<ast::Button>("Simple Button", glm::vec3(100.f, 100.f, 0.f), glm::vec3(64.f, 16.f, 0.f));
    }

    // TODO: Parse a map object through this render function
    void render(ast::OrthoCamera2D& camera, ast::TileMap& map) const
    {
        this->testButton->update(0.f);

        if (this->testButton->isHovering())
            std::cout << "Hovering\n";
        else
            std::cout << "Not Hovering\n";

        // -------------------------------- WORLD --------------------------------
        // Instruct OpenGL to starting using our shader program.
        glUseProgram(shaderProgramId);
        
        glm::mat4 cameraMatrix{camera.getViewMatrix() * camera.getProjectionMatrix()};

        map.render(static_cast<unsigned int>(uniformLocationMVP), cameraMatrix);

        // -------------------------------- GUI --------------------------------
        glUseProgram(guiShaderProgramId);
        this->testButton->render(guiUniformLocationProjection, camera.getProjectionMatrix());
    }

    ~Internal()
    {
        glDeleteProgram(shaderProgramId);
    }
};

OpenGLPipeline::OpenGLPipeline(const std::string& shaderName)
    : internal(ast::make_internal_ptr<Internal>(shaderName)) {}

void OpenGLPipeline::render(ast::OrthoCamera2D& camera, ast::TileMap& map) const
{
    internal->render(camera, map);
}
