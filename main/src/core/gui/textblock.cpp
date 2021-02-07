#include "textblock.hpp"

using ast::TextBlock;

TextBlock::TextBlock(const std::string& text, glm::vec2 pos,
                     glm::vec3 col, float font_size)
{
    this->text = text;
    this->position = pos;
    this->colour = col;
    this->font_size = font_size; 

    float currentLineOffset = 0.f;
    float originalPosition = pos.x;
    int newLineOffset = 2;

    for (unsigned int i = 0; i < text.size(); ++i)
    {
        char glyph = text[i];

        float margin = font_size;
        float spacing = 0.7f;

        if (glyph == ' ')
            continue;
        else if (glyph == '/')
        {
            pos.x -= pos.x + (i + newLineOffset) * (margin * spacing) - originalPosition;
            currentLineOffset += font_size;
            continue;
        }

        glyphs.emplace_back(new Glyph(glyph, (int)text[i], glm::vec2(pos.x + i * (margin * spacing), pos.y + currentLineOffset)));
    }
}

TextBlock::~TextBlock() {
    glyphs.clear();
}
