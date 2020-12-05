
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
        float _textureID;

    public:
        bool& isRepeat();
        float& getUOffset();
        float& getVOffset();
        float& getUScale();
        float& getVScale();
        float& getTextureID();

        void setUOffset(float value);
        void setVOffset(float value);
        void setUScale(float value);
        void setVScale(float value);
        void setTextureID(float value);

        SpriteTexture();
        SpriteTexture(float textureID, float uOffset, float vOffset, float uScale, float vScale, bool repeat);
    };
} // namespace ast