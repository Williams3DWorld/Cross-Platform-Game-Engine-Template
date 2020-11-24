#pragma once

#include "../../core/utils/glm-wrapper.hpp"
#include "../../core/utils/internal-ptr.hpp"

namespace ast
{
    struct OrthoCamera2D
    {
        OrthoCamera2D(const float& width, const float& height);

        void configure(const glm::vec3& position);

        glm::mat4 getProjectionMatrix() const;

        glm::mat4 getViewMatrix() const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
}