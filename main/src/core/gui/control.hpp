#pragma once

#include <iostream>
#include <vector>
#include "../../scene/game-objects/transformObject.hpp"

namespace ast
{
    class Control : public TransformObject
    {
    private:
        std::vector<Control> _children;
    public:
        Control();
        ~Control();

        void addChild(Control child);
        void removeChild(uint16_t idx);

        virtual void update(float dt) override {}
        virtual void render(unsigned int matrix_location = 0, glm::mat4 camera_matrix = glm::mat4(1.f)) override {}
    };
}