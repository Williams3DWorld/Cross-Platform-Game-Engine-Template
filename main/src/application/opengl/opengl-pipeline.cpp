#include "opengl-pipeline.hpp"
#include "../../core/utils/log.hpp"
#include "../../global/tile-settings.hpp"
#include "../../core/audio/audioSystem.hpp"
#include "../../../src/core/renderer/textrenderer.hpp"
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

    // TODO: Move map into a world class
    std::unique_ptr<ast::TileMap> map;

    Internal(const std::string& shaderName)
        : shaderProgramId(::createShaderProgram(shaderName)),
          uniformLocationMVP(glGetUniformLocation(shaderProgramId, "u_mvp")),
          uniformLocationTexture(glGetUniformLocation(shaderProgramId, "u_texture"))
    {
        glUniform1i(uniformLocationTexture, 0);

        // lets play some music :)
        AudioSystem::GetInstance()->Initialise();
        AudioSystem::GetInstance()->addSound("bgm", "assets/sounds/bgm.wav", AudioTypes::MUSIC);
        AudioSystem::GetInstance()->Play("bgm", -1);
        //
    }

    // TODO: Parse a map object through this render function
    void render(ast::OrthoCamera2D& camera, ast::TileMap& map) const
    {
        // -------------------------------- WORLD --------------------------------
        // Instruct OpenGL to starting using our shader program.
        glUseProgram(shaderProgramId);
        
        glm::mat4 cameraMatrix{camera.getViewMatrix() * camera.getProjectionMatrix()};

        map.render(static_cast<unsigned int>(uniformLocationMVP), cameraMatrix);
        // -------------------------------- GUI --------------------------------
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
