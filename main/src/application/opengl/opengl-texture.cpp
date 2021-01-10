#include "opengl-texture.hpp"

using ast::OpenGLTexture;

namespace
{
    GLuint createTexture(const ast::Bitmap& bitmap)
    {
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            bitmap.getWidth(),
            bitmap.getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            bitmap.getPixelData());
        glGenerateMipmap(GL_TEXTURE_2D);

        return textureId;
    }
} // namespace

struct OpenGLTexture::Internal
{
    const GLuint textureId;

    Internal(const ast::Bitmap& bitmap)
        : textureId(::createTexture(bitmap)) {}

    ~Internal()
    {
        glDeleteTextures(1, &textureId);
    }
};

OpenGLTexture::OpenGLTexture(const ast::Bitmap& bitmap)
    : internal(ast::make_internal_ptr<Internal>(bitmap)) {}

const GLuint ast::OpenGLTexture::getID()
{
    return this->internal->textureId;
}

void OpenGLTexture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, internal->textureId);
}
