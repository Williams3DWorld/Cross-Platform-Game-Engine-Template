#pragma once

#include "../../core/utils/graphics-wrapper.hpp"
#include "../../core/renderer/bitmap.hpp"
#include "../../core/utils/internal-ptr.hpp"

namespace ast
{
    struct OpenGLTexture
    {
        OpenGLTexture(const ast::Bitmap& bitmap);

        const GLuint getID();
        void bind() const;

    private:
        struct Internal;
        ast::internal_ptr<Internal> internal;
    };
} // namespace ast
