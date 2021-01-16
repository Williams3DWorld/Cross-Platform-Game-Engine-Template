#ifndef __LAYER_H__
#define __LAYER_H__

#include "../../application/opengl/opengl-batch.hpp"
#include "sprite.hpp"

namespace ast
{
    enum LayerTypes
    {
        SPRITE_LAYER,
        OBJECT_LAYER
    };

    class Layer : public TransformObject
    {
    private:
        unsigned int _layerType;

    public:
        inline unsigned int& getLayerType() { return this->_layerType; }
        virtual void setParent(std::shared_ptr<GameObject> value) override {}
        virtual void addChild(std::shared_ptr<GameObject>& value) override {}
        virtual void update(float dt) override {}
        virtual void render() override {}

        Layer() : _layerType(SPRITE_LAYER) {}
    };
} // namespace ast

#endif