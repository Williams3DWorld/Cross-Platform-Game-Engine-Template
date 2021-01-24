#include "player.hpp"
#include "../../core/utils/sdl-wrapper.hpp"
#include <iostream>
#include "../../application/opengl/opengl-asset-manager.hpp"

using ast::Player;

struct Player::Internal
{
    const float moveSpeed{1.f};
    glm::vec3 position;

    Internal(const glm::vec3& position)
        : position(position) {}

    void moveUp(const float& delta)
    {
        position.y += (moveSpeed * delta);
    }

    void moveDown(const float& delta)
    {
        position.y -= (moveSpeed * delta);
    }

    void moveLeft(const float& delta)
    {
        position.x -= (moveSpeed * delta);
    }

    void moveRight(const float& delta)
    {
        position.x += (moveSpeed * delta);
    }
};

Player::Player(const glm::vec3& position) : internal(ast::make_internal_ptr<Internal>(position))
{
    this->spriteVertex = std::make_unique<SpriteVertex>(glm::vec3(-(0.5f * TILE_SIZE * TILE_SCALE), -(0.5f * TILE_SIZE * TILE_SCALE), .0f), .0f, 35.f);

    std::vector<float> vertexData(spriteVertex->vertexData.begin(), spriteVertex->vertexData.end());
    std::vector<unsigned int> indexData(spriteVertex->indexData.begin(), spriteVertex->indexData.end());

    GLsizei compSize = sizeof(float);
    const auto numAttribs = 7;
    std::vector<AttributeElement> attribElementData({
        {GL_FLOAT, 3, compSize},
        {GL_FLOAT, 2, compSize},
        {GL_FLOAT, 1, compSize},
        {GL_FLOAT, 1, compSize},
    });

    Attribute attribData = {numAttribs, attribElementData};
    this->vbo = std::make_shared<ast::OpenGLBatch>(vertexData, indexData, attribData);
}

glm::vec3 Player::getPosition() const
{
    return internal->position;
}

void Player::moveUp(const float& delta)
{
    internal->moveUp(delta);
}

void Player::moveDown(const float& delta)
{
    internal->moveDown(delta);
}

void Player::moveLeft(const float& delta)
{
    internal->moveLeft(delta);
}

void Player::moveRight(const float& delta)
{
    internal->moveRight(delta);
}

void Player::render(unsigned int& matrix_location,
                    glm::mat4 matrix)
{
    const glm::mat4 identity = glm::mat4(1.f);

    float pixelX = (internal->position.x + 1.0f) * 0.5f * static_cast<float>(ast::sdl::getDisplaySize().first);
    float pixelY = (1.0f - internal->position.y) * 0.5f * static_cast<float>(ast::sdl::getDisplaySize().second);

    const glm::mat4 mvp = matrix * glm::translate(identity, glm::vec3(pixelX, pixelY, internal->position.z));
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &mvp[0][0]);

    OpenGLAssetManager::get().getTexture(0).bind(); // TEMP TEX ID
    this->vbo->bind();
}