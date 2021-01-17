#pragma once

#include "../../core/utils/glm-wrapper.hpp"
#include "../../core/renderer/sprite-vertex.hpp"
#include "../../application/opengl/opengl-batch.hpp"
#include "../../core/utils/internal-ptr.hpp"

namespace ast
{
    class Player 
    {
    public:
        Player(const glm::vec3& position);

        void moveUp(const float& delta);
        void moveDown(const float& delta);
        void moveLeft(const float& delta);
        void moveRight(const float& delta);
        void render(unsigned int & matrix_location, glm::mat4 matrix);

        glm::vec3 getPosition() const;
    private:
        std::unique_ptr<ast::SpriteVertex> spriteVertex;
        std::shared_ptr<ast::OpenGLBatch> vbo;

        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast