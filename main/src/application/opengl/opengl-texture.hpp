#pragma once

#include "../../core/renderer/bitmap.hpp"
#include "../../core/utils/internal-ptr.hpp"

namespace ast
{
    struct OpenGLTexture
    {
        OpenGLTexture(const ast::Bitmap& bitmap);

        void bind() const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
