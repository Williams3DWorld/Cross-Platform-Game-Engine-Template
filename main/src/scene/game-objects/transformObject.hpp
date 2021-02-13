#ifndef __TRANSFORM_OBJECT_H__
#define __TRANSFORM_OBJECT_H__

#include "../../core/utils/glm-wrapper.hpp"
#include "gameObject.hpp"

#define IDENTITY_MATRIX glm::mat4(1.0f)

namespace ast
{
    class TransformObject : public GameObject
    {
    protected:
        bool _visible;
        bool _updatable;
        float _zIndex;
        float _rotation;
        unsigned int _layerID;
        glm::vec3 _scale;
        glm::vec3 _position;
        glm::mat4x4 _model;

    public:
        bool& getVisible();
        bool& updatable();
        float& getZIndex();
        float& getRotation();
        unsigned int& getLayerID();
        glm::vec3& getScale();
        glm::vec3& getPosition();
        glm::mat4& getModel();

        void setVisible(bool value);
        void setUpdatable(bool value);
        void setZIndex(float value);
        void setRotation(float value);
        void setLayerID(unsigned int value);
        void setScale(glm::vec3 value);
        void setPosition(glm::vec3 value);
        void setModel(glm::mat4 value);

        void updateModel();

        virtual void setParent(std::shared_ptr<GameObject> value) override;
        virtual void addChild(std::shared_ptr<GameObject>& value) override;
        virtual void update(float dt) override {}
        virtual void render(unsigned int matrix_location = 0, glm::mat4 camera_matrix = glm::mat4(1.f)) = 0;

        TransformObject();
        TransformObject(const char* name, glm::vec3 position, bool updatable);
    };
} // namespace ast

#endif