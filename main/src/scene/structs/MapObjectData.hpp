#pragma once

#include <iostream>

namespace ast
{
    struct CollisionRectangle
    {
        int x, y = NULL;
        int width, height = NULL;

        CollisionRectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
    };
} 
