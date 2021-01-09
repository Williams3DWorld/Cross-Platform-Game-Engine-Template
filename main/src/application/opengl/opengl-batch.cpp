#include "opengl-batch.hpp"

namespace ast
{
    void OpenGLBatch::create(std::vector<std::any>& vertexData, Attribute& attributeData)
    {
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertexData.size(), this->vertexData.data(), GL_DYNAMIC_DRAW);

        unsigned int pointerOffset = 0;
        for (auto i = 0; i < attributeData.attribElement.size(); i++)
        {
            auto attrib = attributeData.attribElement[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attrib.componentSize, attrib.type, GL_FALSE, attributeData.size * attrib.sizeInBytes, (void*)((size_t)pointerOffset * attrib.sizeInBytes));
        }

        glGenBuffers(1, &this->ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * this->indexData.size(), this->indexData.data(), GL_DYNAMIC_DRAW);
    }

    void OpenGLBatch::bind(unsigned int& textureID)
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->indexData.size()), GL_UNSIGNED_INT, 0);
    }

    void OpenGLBatch::updateSubBufferData(GLintptr offset, GLsizeiptr size, const void* data)
    {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }

    OpenGLBatch::~OpenGLBatch()
    {
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ibo);
        glDeleteVertexArrays(1, &this->vao);
    }
} // namespace ast