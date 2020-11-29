#include "gameObject.hpp"
#include "../../core/utils/glm-wrapper.hpp"

#define IDENTITY_MATRIX glm::mat4(1.0f)

namespace ast
{
    class TransformObject : public GameObject
    {
    private:
        bool        _updatable;
        float       _zIndex;
        float       _rotation;
        glm::vec2   _scale;
        glm::vec2   _position;
        glm::mat4x4 _model;

    public:
        bool& updatable();
        float& getZIndex();
        float &getRotation();
        glm::vec2 &getScale();
        glm::vec2& getPosition();
        glm::mat4 &getModel();

        void setUpdatable(bool value);
        void setZIndex(float value);
        void setRotation(float value);
        void setScale(glm::vec2 value);
        void setPosition(glm::vec2 value);
        void setModel(glm::mat4 value);

        void updateModel();

        virtual void setParent(std::shared_ptr<GameObject> value) override;
        virtual void addChild(std::shared_ptr<GameObject>& value) override;
        virtual void update(float dt) {}

        TransformObject(const char* name, glm::vec2 position, bool updatable);
    };
}