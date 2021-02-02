#include "game.hpp"

#include "collisionManager.hpp"

namespace ast
{
    Game::Game(float& screenWidth, float& screenHeight)
    {
        this->_keyboardState = SDL_GetKeyboardState(nullptr);
        this->_camera = std::make_unique<OrthoCamera2D>(screenWidth, screenHeight);

        this->prepare();

        // TEMP!
        auto tiledMap = ast::OpenGLAssetManager::get().getTiledMap("multi-layer-chunk-test.tmx");
        auto spriteLayers = ast::LayerHelper::createSpriteLayersFromTiledMap(tiledMap);
        this->_collisions = ast::LayerHelper::createCollisionDataFromTiledLayer(tiledMap);

        std::map<unsigned int, std::shared_ptr<Layer>> layerData;
        for (auto const& layer : spriteLayers)
            layerData[layer->getLayerID()] = layer;

        this->_map = std::make_unique<TileMap>(0, 0, layerData, this->_collisions);
    }

    std::unique_ptr<ast::OrthoCamera2D>& Game::getCamera()
    {
        return this->_camera;
    }

    std::unique_ptr<ast::TileMap>& Game::getMap()
    {
        return this->_map;
    }

    void Game::prepare()
    {
        ast::OpenGLAssetManager::get().loadAssetsFromFile("assets/assets.xml");
        ast::OpenGLAssetManager::get().loadTiledMap("multi-layer-chunk-test.tmx");
        ast::OpenGLAssetManager::get().loadPipelines();
    }

    void Game::processInput(float dt)
    {
        if (this->_keyboardState[SDL_SCANCODE_W])
            this->_map->getPlayer()->moveUp(dt);
        if (this->_keyboardState[SDL_SCANCODE_S])
            this->_map->getPlayer()->moveDown(dt);
        if (this->_keyboardState[SDL_SCANCODE_A])
            this->_map->getPlayer()->moveLeft(dt);
        if (this->_keyboardState[SDL_SCANCODE_D])
            this->_map->getPlayer()->moveRight(dt);
    }

    void Game::update(float dt)
    {
        this->processInput(dt);
        this->_camera->configure(this->_map->getPlayer()->getPosition());

        for (auto i = 0; i < this->_collisions.size(); ++i) {
            ast::CollisionManager::get().evalulateCollision(*this->_map->getPlayer(), *this->_map->getPlayer()->collisionRectangle, this->_collisions[i], dt);
        }
    }

} // namespace ast