#include "player.hpp"

using ast::Player;

struct Player::Internal
{

    const float moveSpeed{5.0f};
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

Player::Player(const glm::vec3& position) : internal(ast::make_internal_ptr<Internal>(position)) {}

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