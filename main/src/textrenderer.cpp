#include "textrenderer.hpp"

using ast::TextRenderer;

void TextRenderer::addText(const std::string& text, glm::vec2 pos, glm::vec3 col, float size)
{
    this->textBlocks.push_back(new ast::TextBlock(text.c_str(), pos, col, size));

    this->batches.push_back(new TextBatch());

    for (Uint16 i = 0; i < this->textBlocks[this->textBlocks.size() - 1]->GetGlyphs().size(); ++i)
    {
        auto offsetCount = 0;

        const CharacterVertex characterVertex = CharacterVertex(this->textBlocks[this->textBlocks.size() - 1]->GetGlyphs()[i]->position,
                                                                glm::vec2(this->textBlocks[this->textBlocks.size() - 1]->GetFontSize()), 
                                                                this->textBlocks[this->textBlocks.size() - 1]->GetGlyphs()[i]->ascii_code);

        for (auto vertexFloatValue : characterVertex.vertexData)
            this->batches[batches.size() - 1]->vertexData.emplace_back(vertexFloatValue);
        for (auto indexValue : characterVertex.indexData)
        {
            unsigned int indexOffset = indexValue + RECT_VERTEX_COUNT * static_cast<unsigned int>(this->batches[batches.size() - 1]->offsetData.size());
            this->batches[batches.size() - 1]->indexData.emplace_back(indexOffset);
        }

        this->batches[batches.size() - 1]->offsetData[i] = offsetCount;
        offsetCount++;
    }

    glGenVertexArrays(1, &this->batches[batches.size() - 1]->vao);
    glBindVertexArray(this->batches[batches.size() - 1]->vao);

    glGenBuffers(1, &this->batches[batches.size() - 1]->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->batches[batches.size() - 1]->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->batches[batches.size() - 1]->vertexData.size(), this->batches[batches.size() - 1]->vertexData.data(), GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); // VERTEX POSITIONS
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); // TEXCOORDS
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2); // TILE ID
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));

    glGenBuffers(1, &this->batches[batches.size() - 1]->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->batches[batches.size() - 1]->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * this->batches[batches.size() - 1]->indexData.size(), this->batches[batches.size() - 1]->indexData.data(), GL_DYNAMIC_DRAW);
}

void TextRenderer::loadFontSheet(const std::string& file)
{
    this->gltexture = new ast::OpenGLTexture(ast::assets::loadBitmap("assets/locale/" + file + ".png"));
}

void TextRenderer::render()
{
    glActiveTexture(GL_TEXTURE2);
    this->gltexture->bind();

    for (Uint16 i = 0; i < this->batches.size(); i++)
    {
        glBindVertexArray(this->batches[i]->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->batches[i]->ibo);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->batches[i]->indexData.size()), GL_UNSIGNED_INT, 0);
    }
}

TextRenderer* TextRenderer::instance;
