#include "player.hpp"
#include <iostream>

using ast::Player;

struct Player::Internal
{
    const float moveSpeed{.4f};
    glm::vec3 position;

    Internal(const glm::vec3& position)
        : 
          position(position) {}

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
    this->spriteVertex = std::make_unique<SpriteVertex>(position, 0, 50);

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

void Player::render(unsigned int& matrix_location, glm::mat4& matrix)
{
    glm::mat4 player_matrix = glm::mat4(1.f);
    player_matrix = matrix * glm::translate(player_matrix, glm::vec3(internal->position.x, internal->position.y, internal->position.z));
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &player_matrix[0][0]);

    unsigned int id = 0;
    this->vbo->bind(id);
}