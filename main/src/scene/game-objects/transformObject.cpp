#include "transformObject.hpp"

namespace ast
{
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

    TransformObject::TransformObject() : _zIndex(0.0f), _rotation(0), _scale({1.f, 1.f, 1.f}), _position(glm::vec3(.0f)), _model(IDENTITY_MATRIX), _updatable(true)
    {
        this->_name = "TransformObject";
        this->_type = TRANSFORM_OBJECT;
    }

    TransformObject::TransformObject(const char* name = "TransformObject", glm::vec3 position = {.0f, .0f, .0f}, bool updatable = true) : _zIndex(0.0f), _rotation(0), _scale({1.f, 1.f, 1.f}), _position(position), _model(IDENTITY_MATRIX), _updatable(updatable)
    {
        this->_name = name;
        this->_position = position;
        this->_updatable = updatable;

        this->_type = TRANSFORM_OBJECT;
    }

} // namespace ast