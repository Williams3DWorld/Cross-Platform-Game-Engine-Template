#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <glm/glm.hpp>

#include "../src/scene/game-objects/player.hpp"
#include "../src/scene/structs/MapObjectData.hpp"

#define PI 3.14159265
#define SEMICIRCLE 180.f
#define RIGHTANGLE 90.f
#define ELIPSOID 200.f

namespace ast
{
    class CollisionManager 
    {
    private:
    public:
        inline static CollisionManager& get()
        {
            static CollisionManager collisionManager;
            return collisionManager;
        }

        inline bool evalulateCollision(ast::Player& player, ast::CollisionRectangle& a, ast::CollisionRectangle& b, float dt)
        {
            glm::vec2 otherPosition = glm::vec2(b.x + (b.width / 2), b.y + (b.height / 2));
            glm::vec2 otherHalfSize = glm::vec2(b.width / 2, b.height / 2);

            glm::vec2 thisPosition = glm::vec2(a.x, a.y + (a.height / 2));
            glm::vec2 thisHalfSize = glm::vec2(a.width, a.height / 2);

            float deltaX = otherPosition.x - thisPosition.x;
            float deltaY = otherPosition.y - thisPosition.y;
            float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
            float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

            if (intersectX < 0.0f && intersectY < 0.0f)
            {
                if (intersectX > intersectY)
                {
                    if (deltaX > 0.0f)
                    {
                        player.moveRight(intersectX * 1.0f * dt);
                    }
                    else 
                    {
                        player.moveRight(-intersectX * 1.0f * dt);
                    }
                }
                else 
                {
                    if (deltaY > 0.0f)
                    {
                        player.moveDown(intersectY * 1.0f * dt);
                    }
                    else
                    {
                        player.moveDown(-intersectY * 1.0f * dt);
                    }
                }

                return true;
            }

            return false;
        }
    };
}