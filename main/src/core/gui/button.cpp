#include "button.hpp"

namespace ast
{
    Button::Button(const std::string& label, glm::vec2 position, glm::vec2 size) 
    {
        this->_position = glm::vec3(position.x, position.y, 1.f);
        this->_scale = glm::vec3(size.x, size.y, 0.f);

        this->_pressed = false;

        this->spriteVertex = std::make_unique<SpriteVertex>(
            glm::vec3(.0f, .0f, .0f), 0, 0, glm::vec2(size.x, size.y), glm::vec3(1.f, 1.f, 1.f));

        std::vector<float> vertexData(spriteVertex->vertexData.begin(), spriteVertex->vertexData.end());
        std::vector<unsigned int> indexData(spriteVertex->indexData.begin(), spriteVertex->indexData.end());

        GLsizei compSize = sizeof(float);
        const auto numAttribs = 7;
        std::vector<AttributeElement> attribElementData({
            {GL_FLOAT, 3, compSize},
            {GL_FLOAT, 2, compSize},
            {GL_FLOAT, 1, compSize},
            {GL_FLOAT, 1, compSize},
        });

        Attribute attribData = {numAttribs, attribElementData};
        this->vbo = std::make_shared<ast::OpenGLBatch>(vertexData, indexData, attribData);
    }
    Button::~Button() {}

    bool& Button::isPressed()
    {
        return this->_pressed;
    }

    bool& Button::isHovering()
    {
        return this->_hovering;
    }

    void Button::update(float dt) {
        // @todo: Move this into an input class of some sort
        // but its here for now to test the button functionality code
        // shown below through the aabb formatted check
        int x, y;
        SDL_GetMouseState(&x, &y);
        //

        if ((float)x < this->_position.x + this->_scale.x * TILE_SCALE &&
            (float)x > this->_position.x - this->_scale.x / TILE_SCALE &&
            (float)y < this->_position.y + this->_scale.y * TILE_SCALE &&
            (float)y > this->_position.y - this->_scale.y / TILE_SCALE)
        {
            this->_hovering = true;
        }
        else
            this->_hovering = false;
    }

    void Button::render(unsigned int matrix_location, glm::mat4 camera_matrix) {
        const glm::mat4 identity = glm::mat4(1.f);

        glm::mat4 transformMatrix = camera_matrix *
                                    glm::translate(identity, this->_position);

        glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &transformMatrix[0][0]);

        this->vbo->bind();
    }
}