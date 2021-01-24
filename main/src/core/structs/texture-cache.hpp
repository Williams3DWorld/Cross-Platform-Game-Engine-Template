#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include "../../application/opengl/opengl-texture.hpp"

namespace ast
{
    struct TextureCache
    {
        int index;
        ast::OpenGLTexture& texture;

        TextureCache(ast::OpenGLTexture& tex) : texture(tex)
        {
            static int indexCounter;
            this->index = indexCounter;
            indexCounter++;
        }
    };
} // namespace ast

#endif