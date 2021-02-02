#ifndef __GAME_H__
#define __GAME_H__

#include "data/gameData.hpp"
#include "core/utils/sdl-wrapper.hpp"
#include "core/camera/ortho-camera-2d.hpp"
#include "core/utils/tmx/map-parser.hpp"
#include "global/player-settings.hpp"
#include "application/opengl/opengl-renderer.hpp"
#include "scene/game-objects/tileMap.hpp"
#include "scene/utils/layer-helper.hpp"
#include "scene/game-objects/tileMap.hpp"
#include <memory>

namespace ast
{
    class Game
    {
    private:
        ast::GameData                           _gameData;
        std::unique_ptr<ast::OrthoCamera2D>     _camera;
        std::unique_ptr<ast::TileMap>           _map;
        const uint8_t*                          _keyboardState;
    
        std::vector<ast::CollisionRectangle>    _collisions;
    public:
        Game(float& screenWidth, float& screenHeight);

        std::unique_ptr<ast::TileMap>&          getMap();
        std::unique_ptr<ast::OrthoCamera2D>&    getCamera();

        void prepare();
        void processInput(float dt);
        void update(float dt);
    };
}

#endif