#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <iostream>
#include <SDL.h>
#include "../../core/gui/control.hpp"
#include "../../application/opengl/opengl-batch.hpp"
#include "../../core/renderer/sprite-vertex.hpp"

namespace ast
{
    class Button : public Control
    {
    private:
        bool _pressed;
        bool _hovering;
        std::unique_ptr<ast::SpriteVertex> spriteVertex;
        std::shared_ptr<ast::OpenGLBatch> vbo;
    public:
        Button(const std::string& label, glm::vec2 position, glm::vec2 size);
        ~Button();

        bool &isPressed();
        bool &isHovering();

        virtual void update(float dt);
        virtual void render(unsigned int matrix_location = 0, glm::mat4 camera_matrix = glm::mat4(1.f));
    };
}

#endif