#pragma once

#include "../../core/utils/glm-wrapper.hpp"
#include "../../core/utils/internal-ptr.hpp"

namespace ast
{
    struct Player 
    {
        Player(const glm::vec3& position);

        void moveUp(const float& delta);

        void moveDown(const float& delta);

        void moveLeft(const float& delta);
        
        void moveRight(const float& delta);

        glm::vec3 getPosition() const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast