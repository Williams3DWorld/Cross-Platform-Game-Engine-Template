#pragma once

#include <iostream>
#include <vector>
#include "textblock.hpp"
#include "../src/core/renderer/character-vertex.hpp"

#define NUM_ATTRIBS 3
#define VERTEX_STRIDE 8

namespace ast
{
    struct TextBatch
    {
        unsigned int vao;
        unsigned int vbo;
        unsigned int ibo;

        std::vector<float> vertexData;
        std::vector<unsigned int> indexData;
        std::unordered_map<unsigned int, unsigned int> offsetData;

        void updateSubData(unsigned int spriteID, float data[])
        {
            auto vertex = 0;
            for (auto i = spriteID * VERTEX_STRIDE; i < VERTEX_STRIDE; i++)
            {
                this->vertexData[i] = data[vertex];
                vertex++;
            }
        }

        TextBatch() : vbo(0), vao(0), ibo(0) {}
    };

    class TextRenderer
    {
    private:
        std::vector<TextBatch*> batches;

        ast::OpenGLTexture* gltexture;

        std::vector<ast::TextBlock*> textBlocks;
        std::unique_ptr<ast::OpenGLTexture> bitmapFont;

        static TextRenderer* instance;
    public:
        TextRenderer() = default;
        ~TextRenderer() {}

        static TextRenderer* GetInstance()
        {
            if (!instance)
                instance = new TextRenderer();

            return instance;
        }

        void loadFontSheet(const std::string& file);
        void addText(const std::string& text, glm::vec2 pos, glm::vec3 col, float size);
        void render();
    };
}