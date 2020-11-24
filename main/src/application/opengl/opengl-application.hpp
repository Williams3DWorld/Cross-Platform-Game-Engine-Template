#pragma once

#include "../../core/utils/internal-ptr.hpp"
#include "../application.hpp"

namespace ast
{
    struct OpenGLApplication : public ast::Application
    {
        OpenGLApplication();

		void update(const float& delta) override;

        void render() override;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
