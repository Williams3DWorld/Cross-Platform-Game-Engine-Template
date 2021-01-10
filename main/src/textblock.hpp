#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <glm/glm.hpp>

#include "../src/application/opengl/opengl-texture.hpp"
#include "../src/application/opengl/opengl-batch.hpp"
#include "../src/core/utils/assets.hpp"

namespace ast
{
    struct Glyph
    {
        char glyph;
        int ascii_code;
        glm::vec2 position;

        Glyph(char gly, int code, glm::vec2 pos)
        {
            this->glyph = gly;
            this->ascii_code = code;
            this->position = pos;
        }
    };

    class TextBlock 
    {
    private:
        std::string text;
        std::vector<Glyph*> glyphs;

        glm::vec2 position;
        glm::vec3 colour;
        float font_size;
        float spacing;
    public:
        TextBlock(const std::string& text, glm::vec2 pos, 
            glm::vec3 col, float font_size = 1.f);
        ~TextBlock();

        inline float &GetFontSize() {
            return font_size;
        }

        inline std::vector<Glyph*> GetGlyphs() const {
            return glyphs;
        }
    };
}