#pragma once

#include <iostream>

namespace ast
{
    struct CollisionRectangle
    {
        float x, y = NULL;
        float width, height = NULL;

        void updatePosition(float x, float y) {
            this->x = x;
            this->y = y;
        }

        CollisionRectangle(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
    };
} 
