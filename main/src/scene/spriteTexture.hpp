
namespace ast
{
    class SpriteTexture
    {
    private:
        bool _repeat;
        float _uOffset;
        float _vOffset;
        float _uScale;
        float _vScale;
        unsigned int _textureID;

    public:
        bool& isRepeat();
        float& getUOffset();
        float& getVOffset();
        float& getUScale();
        float& getVScale();
        unsigned int& getTextureID();

        void setUOffset(float value);
        void setVOffset(float value);
        void setUScale(float value);
        void setVScale(float value);
        void setTextureID(unsigned int value);

        SpriteTexture();
        SpriteTexture(unsigned int textureID, float uOffset, float vOffset, float uScale, float vScale, bool repeat);
    };
} // namespace ast