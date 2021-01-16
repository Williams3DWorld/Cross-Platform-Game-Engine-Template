#include "game.hpp"

namespace ast
{
    Game::Game(float& screenWidth, float& screenHeight, ast::OpenGLAssetManager& assetManager)
    {
        this->_keyboardState = SDL_GetKeyboardState(nullptr);
        this->_camera = std::make_unique<OrthoCamera2D>(screenWidth, screenHeight);
        this->_player = std::make_unique<Player>(glm::vec3(.0f, .0f, -PLAYER_RADIUS));
        
        this->prepare(assetManager);

        // TEMP!
        auto tiledMap = assetManager.getTiledMap("multi-layer-chunk-test.tmx");
        auto spriteLayers = ast::LayerHelper::createSpriteLayersFromTiledMap(tiledMap);
        std::map<unsigned int, std::shared_ptr<Layer>> layerData;
        for (auto const& layer : spriteLayers)
            layerData[layer->getLayerID()] = layer;
        this->_map = std::make_unique<TileMap>(0, 0, layerData);
    }

    std::unique_ptr<ast::OrthoCamera2D>& Game::getCamera()
    {
        return this->_camera;
    }

    std::unique_ptr<ast::TileMap>& Game::getMap()
    {
        return this->_map;
    }

    void Game::prepare(ast::OpenGLAssetManager& assetManager)
    {
        assetManager.loadTextures({"buch-outdoor.png"});
        assetManager.loadTiledMap("multi-layer-chunk-test.tmx");
        assetManager.loadPipelines(assetManager);
    }

    void Game::processInput(float dt)
    {
        if (this->_keyboardState[SDL_SCANCODE_W])
            this->_player->moveUp(dt);
        if (this->_keyboardState[SDL_SCANCODE_S])
            this->_player->moveDown(dt);
        if (this->_keyboardState[SDL_SCANCODE_A])
            this->_player->moveLeft(dt);
        if (this->_keyboardState[SDL_SCANCODE_D])
            this->_player->moveRight(dt);
    }

    void Game::update(float dt)
    {
        this->processInput(dt);
        this->_camera->configure(this->_player->getPosition());
    }

    void Game::render()
    {
        this->_map->render();
    }

} // namespace ast