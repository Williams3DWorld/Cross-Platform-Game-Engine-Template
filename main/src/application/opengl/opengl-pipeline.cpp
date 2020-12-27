#include "opengl-pipeline.hpp"
#include "../../application/opengl/opengl-sprite-renderer.hpp"
#include "../../core/utils/assets.hpp"
#include "../../core/utils/log.hpp"
#include "../../core/utils/map-parser.hpp"
#include "opengl-asset-manager.hpp"
#include <GL/glew.h>
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

    // TEST
    std::unique_ptr<ast::OpenGLSpriteRenderer> spriteRenderer;

    Internal(const std::string& shaderName)
        : shaderProgramId(::createShaderProgram(shaderName)),
          uniformLocationMVP(glGetUniformLocation(shaderProgramId, "u_mvp")),
          uniformLocationTexture(glGetUniformLocation(shaderProgramId, "u_textures[0]"))
    {
        // --------------- MAP TEST --------------------
        ast::MapParser* parser = new ast::MapParser();
        parser->parse("demo.tmx");

        const unsigned int mapWidth = 2;
        const unsigned int mapHeight = 2;
        const unsigned int numTiles = 4;
        unsigned int test_map[numTiles] = {4, 18, 7, 26};

        for (auto i = 0; i < numTiles; i++)
        {
            GameObjectPool::gameObjects["Sprite" + i] = std::make_shared<Sprite>("Sprite" + i);
            auto posOffset = glm::vec3(static_cast<float>(i % mapWidth) * 64.f, static_cast<float>(floor(i / mapHeight)) * 64.f, .0f);
            std::dynamic_pointer_cast<TransformObject>(GameObjectPool::gameObjects["Sprite" + i])->setPosition(posOffset);
            std::dynamic_pointer_cast<Sprite>(GameObjectPool::gameObjects["Sprite" + i])->setTileID(static_cast<float>(test_map[i]));
        }
        // --------------- MAP TEST --------------------

        this->spriteRenderer = std::make_unique<OpenGLSpriteRenderer>();
        glUniform1i(uniformLocationTexture, 0);
    }

    void render(ast::OrthoCamera2D& camera) const
    {
        const glm::mat4 identity = glm::mat4(1.f);
        const glm::mat4 cameraMatrix{camera.getViewMatrix() * camera.getProjectionMatrix()};
        const glm::mat4 mvp = cameraMatrix *
                              glm::translate(identity, glm::vec3(.0f, .0f, .0f));
        /*  *
                                          glm::rotate(identity, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f)) *
                                          glm::scale(identity, glm::vec3(1.f));*/

        // Instruct OpenGL to starting using our shader program.
        glUseProgram(shaderProgramId);

        // Populate the 'u_mvp' uniform in the shader program.
        glUniformMatrix4fv(uniformLocationMVP, 1, GL_FALSE, &mvp[0][0]);

        // TEST
        this->spriteRenderer->render();
    }

    ~Internal()
    {
        glDeleteProgram(shaderProgramId);
    }
};

OpenGLPipeline::OpenGLPipeline(const std::string& shaderName)
    : internal(ast::make_internal_ptr<Internal>(shaderName)) {}

void OpenGLPipeline::render(ast::OrthoCamera2D& camera) const
{
    internal->render(camera);
}
