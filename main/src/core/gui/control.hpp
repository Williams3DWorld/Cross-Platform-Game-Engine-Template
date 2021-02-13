#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "../../scene/game-objects/transformObject.hpp"

namespace ast
{
    class Control : public TransformObject
    {
    private:
        uint16_t _elementId;
    public:
        virtual void update(float dt) {}
        virtual void render(unsigned int matrix_location = 0, glm::mat4 camera_matrix = glm::mat4(1.f)) {}

        Control() {}
        ~Control() {}
    };
} // namespace ast

#endif