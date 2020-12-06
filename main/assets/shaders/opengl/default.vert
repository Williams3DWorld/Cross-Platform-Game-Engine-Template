attribute vec3 vertexPosition;

uniform mat4 u_mvp;

void main()
{
    gl_Position = u_mvp * vec4(vertexPosition, 1.0);
}
