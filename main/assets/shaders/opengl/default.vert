attribute vec3 vertexPosition;
attribute float textureID;

uniform mat4 u_mvp;

varying float v_textureID;

void main()
{
    gl_Position = u_mvp * vec4(vertexPosition, 1.0);
    v_textureID = textureID;
}
