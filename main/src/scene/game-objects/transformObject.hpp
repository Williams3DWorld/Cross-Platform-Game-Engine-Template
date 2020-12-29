#include "../../core/utils/glm-wrapper.hpp"
#include "gameObject.hpp"

#define IDENTITY_MATRIX glm::mat4(1.0f)

namespace ast
{
    class TransformObject : public GameObject
    {
    protected:
        bool _updatable;
        float _zIndex;
        float _rotation;
        glm::vec3 _scale;
        glm::vec3 _position;
        glm::mat4x4 _model;

    public:
        bool& updatable();
        float& getZIndex();
        float& getRotation();
        glm::vec3& getScale();
        glm::vec3& getPosition();
        glm::mat4& getModel();

        void setUpdatable(bool value);
        void setZIndex(float value);
        void setRotation(float value);
        void setScale(glm::vec3 value);
        void setPosition(glm::vec3 value);
        void setModel(glm::mat4 value);

        void updateModel();

        virtual void setParent(std::shared_ptr<GameObject> value) override;
        virtual void addChild(std::shared_ptr<GameObject>& value) override;
        virtual void update(float dt) override {}

        TransformObject();
        TransformObject(const char* name, glm::vec3 position, bool updatable);
    };
} // namespace ast