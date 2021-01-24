#ifndef __OPENGL_BATCH_H__
#define __OPENGL_BATCH_H__

#include "../../core/utils/graphics-wrapper.hpp"
#include <any>
#include <map>
#include <vector>

namespace ast
{
    struct AttributeElement
    {
        GLenum type;
        GLint componentSize;
        GLsizei sizeInBytes;
    };

    struct Attribute
    {
        GLsizei size;
        std::vector<AttributeElement> attribElement;
    };

    class OpenGLBatch
    {
    private:
        unsigned int vao;
        unsigned int vbo;
        unsigned int ibo;

        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;

    public:
        void create(std::vector<float>& vertexData, std::vector<unsigned int>& indexData, Attribute& attributeData);
        void bind();
        void updateSubBufferData(GLintptr offset, GLsizeiptr size, const void* data);

        OpenGLBatch(std::vector<float>& vertexData, std::vector<unsigned int>& indexData, Attribute& attributeData);
        ~OpenGLBatch();
    };
} // namespace ast

#endif