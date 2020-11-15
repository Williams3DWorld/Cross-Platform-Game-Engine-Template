#include "ortho-camera-2d.hpp"

using ast::OrthoCamera2D;

struct OrthoCamera2D::Internal
{
    const glm::mat4 projectionMatrix;
    glm::vec3 position;

    Internal(const float& width, const float& height) 
        : projectionMatrix(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)),
          position(glm::vec3(0.0f)) {}

};

OrthoCamera2D::OrthoCamera2D(const float& width, const float&height) : internal(ast::make_internal_ptr<Internal>(width, height)) {}

void OrthoCamera2D::configure(const glm::vec3& position)
{
    internal->position = position;
}

glm::mat4 OrthoCamera2D::getProjectionMatrix() const
{
    return internal->projectionMatrix;
}

glm::mat4 OrthoCamera2D::getViewMatrix() const
{
    return glm::lookAt(internal->position, glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}