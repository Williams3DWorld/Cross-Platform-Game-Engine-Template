#include "opengl-pipeline.hpp"
#include "../../application/opengl/opengl-batch-renderer.hpp"
#include "../../core/utils/assets.hpp"
#include "../../core/utils/log.hpp"
#include "../../global/tile-settings.hpp"
#include "opengl-asset-manager.hpp"
#include "../../core/audio/audioSystem.hpp"
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
    std::unique_ptr<ast::OpenGLBatchRenderer> spriteRenderer;

    Internal(const std::string& shaderName, ast::OpenGLAssetManager& assetManager)
        : shaderProgramId(::createShaderProgram(shaderName)),
          uniformLocationMVP(glGetUniformLocation(shaderProgramId, "u_mvp")),
          uniformLocationTexture(glGetUniformLocation(shaderProgramId, "u_textures[0]"))
    {
        // --------------- MAP TEST --------------------
        ast::TiledMap map = ast::MapParser::GetInstance()->parse("assets/maps/multi-layer-chunk-test.tmx");

        ast::TiledLayer layer0 = map.layers[0];
        ast::TiledLayer layer1 = map.layers[1];

        for (auto i = 0; i < layer0.tileIDs.size(); i++)
        {
            if (layer0.tileIDs[i] == 0)
                continue;

            GameObjectPool::gameObjects["Sprite" + i] = std::make_shared<Sprite>("Sprite" + i);
            auto posOffset = glm::vec3(static_cast<float>(i % layer0.width) * TILE_SIZE * TILE_SCALE,
                                       static_cast<float>(floor(i / layer0.width)) * TILE_SIZE * TILE_SCALE, .0f);
            std::dynamic_pointer_cast<TransformObject>(GameObjectPool::gameObjects["Sprite" + i])->setPosition(posOffset);
            std::dynamic_pointer_cast<Sprite>(GameObjectPool::gameObjects["Sprite" + i])->setTileID(static_cast<float>(layer0.tileIDs[i] - 1));
        }
        for (auto i = 0; i < layer1.tileIDs.size(); i++)
        {
            if (layer1.tileIDs[i] == 0)
                continue;

            GameObjectPool::gameObjects["Sprite" + i] = std::make_shared<Sprite>("Sprite" + i);
            auto posOffset = glm::vec3(static_cast<float>(i % layer1.width) * TILE_SIZE * TILE_SCALE,
                                       static_cast<float>(floor(i / layer1.width)) * TILE_SIZE * TILE_SCALE, .0f);
            std::dynamic_pointer_cast<TransformObject>(GameObjectPool::gameObjects["Sprite" + i])->setPosition(posOffset);
            std::dynamic_pointer_cast<Sprite>(GameObjectPool::gameObjects["Sprite" + i])->setTileID(static_cast<float>(layer1.tileIDs[i] - 1));
        }
        // --------------- MAP TEST --------------------

        AudioSystem::GetInstance()->Initialise();
        AudioSystem::GetInstance()->addSound("music", "assets/sounds/bgm.wav", ast::AudioTypes::MUSIC);
        AudioSystem::GetInstance()->Play("music", -1);

        this->spriteRenderer = std::make_unique<OpenGLBatchRenderer>();
        glUniform1i(uniformLocationTexture, 0);
    }

    // TODO: Parse a map object through this render function
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

OpenGLPipeline::OpenGLPipeline(const std::string& shaderName, ast::OpenGLAssetManager& assetManager)
    : internal(ast::make_internal_ptr<Internal>(shaderName, assetManager)) {}

void OpenGLPipeline::render(ast::OrthoCamera2D& camera) const
{
    internal->render(camera);
}
