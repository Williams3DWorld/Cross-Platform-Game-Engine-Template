#include "transformObject.hpp"

namespace ast
{
    bool& TransformObject::getVisible()
    {
        return this->_visible;
    }

    bool& TransformObject::updatable()
    {
        return this->_updatable;
    }

    float& TransformObject::getZIndex()
    {
        return this->_zIndex;
    }

    float& TransformObject::getRotation()
    {
        return this->_rotation;
    }

    unsigned int& TransformObject::getLayerID()
    {
        return this->_layerID;
    }

    glm::vec3& TransformObject::getScale()
    {
        return this->_scale;
    }

    glm::vec3& TransformObject::getPosition()
    {
        return this->_position;
    }

    glm::mat4& TransformObject::getModel()
    {
        return this->_model;
    }

    void TransformObject::setVisible(bool value)
    {
        this->_visible = value;
    }

    void TransformObject::setUpdatable(bool value)
    {
        this->_updatable = value;
    }

    void TransformObject::setZIndex(float value)
    {
        this->_zIndex = value;
    }

    void TransformObject::setRotation(float value)
    {
        this->_rotation = value;
    }

    void TransformObject::setLayerID(unsigned int value)
    {
        this->_layerID = value;
    }

    void TransformObject::setScale(glm::vec3 value)
    {
        this->_scale = value;
    }

    void TransformObject::setPosition(glm::vec3 value)
    {
        this->_position = value;
    }

    void TransformObject::setModel(glm::mat4 value)
    {
        this->_model = value;
    }

    void TransformObject::setParent(std::shared_ptr<GameObject> value)
    {
        if (value != nullptr)
        {
            this->_parent = value;
        }
    }

    void TransformObject::updateModel()
    {
        this->_model = glm::translate(IDENTITY_MATRIX, glm::vec3(this->_position.x, this->_position.y, this->_zIndex)) *
                       glm::rotate(IDENTITY_MATRIX, glm::radians(this->_rotation), glm::vec3(.0f, .0f, 1.f)) *
                       glm::scale(IDENTITY_MATRIX, glm::vec3(this->_scale.x, this->_scale.y, 1.f));

        if (this->_parent)
            this->_model *= std::dynamic_pointer_cast<TransformObject>(this->_parent)->getModel();
    }

    void TransformObject::addChild(std::shared_ptr<GameObject>& value)
    {
        if (value != nullptr)
        {
            if (this->_children.find(value->getName()) == this->_children.end())
            {
                std::dynamic_pointer_cast<TransformObject>(value)->setZIndex(this->_zIndex);
                value->setParent(std::shared_ptr<GameObject>(this));
                this->_children[value->getName()] = value;

                this->updateModel();
            }
        }

    }

    TransformObject::TransformObject()
    {
        this->_name = "TransformObject";
        this->_type = TRANSFORM_OBJECT;
        this->_visible = true;
        this->_updatable = true;
        this->_layerID = 0;
        this->_zIndex = 0;
        this->_rotation = .0f;
        this->_position = glm::vec3(.0f);
        this->_scale = glm::vec3(1.f);
        this->_model = IDENTITY_MATRIX;
    }
    
    TransformObject::TransformObject(const char* name, glm::vec3 position = {.0f, .0f, .0f}, bool updatable = true) : _zIndex(0.0f), _rotation(0), _scale({1.f, 1.f, 1.f}), _position(position), _model(IDENTITY_MATRIX), _visible(true), _updatable(updatable), _layerID(0)
    {
        this->_name = name;
        this->_position = position;
        this->_updatable = updatable;

        this->_type = TRANSFORM_OBJECT;
    }

} // namespace ast