#pragma once

#include "../core/utils/internal-ptr.hpp"

namespace ast
{
    struct Application
    {
        Application();

        virtual ~Application() = default;

        void startApplication();

        bool runMainLoop();

        virtual void update(const float& delta) = 0;

        virtual void render() = 0;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
