#include "opengl-batch.hpp"
#include <iostream>

namespace ast
{
    void OpenGLBatch::create(std::vector<float>& vertexData, std::vector<unsigned int>& indexData, Attribute& attributeData)
    {
        if (vertexData.empty() || indexData.empty())
        {
            std::cerr << "Error: Vertex or index data is invalid!\n";
            return;
        }

        this->vertexData = vertexData;
        this->indexData = indexData;

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertexData.size(), this->vertexData.data(), GL_DYNAMIC_DRAW);

        size_t pointerOffset = 0;
        for (auto i = 0; i < attributeData.attribElement.size(); i++)
        {
            auto attrib = attributeData.attribElement[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attrib.componentSize, attrib.type, GL_FALSE, attributeData.size * attrib.sizeInBytes, (void*)(pointerOffset * attrib.sizeInBytes));

            pointerOffset += attrib.componentSize;
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

    OpenGLBatch::OpenGLBatch(std::vector<float>& vertexData, std::vector<unsigned int>& indexData, Attribute& attributeData)
    {
        this->create(vertexData, indexData, attributeData);
    }

    OpenGLBatch::~OpenGLBatch()
    {
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ibo);
        glDeleteVertexArrays(1, &this->vao);
    }
} // namespace ast