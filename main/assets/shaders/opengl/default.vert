attribute vec3 vertexPosition;
attribute vec2 vertexTexcoord;
attribute float vertexTexID;
attribute float vertexTileID;

uniform mat4 u_mvp;

varying float texID;
varying float tileID;
varying vec2 texCoord;

void main()
{
	texID = vertexTexID;
	tileID = vertexTileID;
	texCoord = vertexTexcoord;
    gl_Position = u_mvp * vec4(vertexPosition, 1.0);
}
