attribute vec3 vertexPosition;
attribute vec2 vertexTexcoord;
attribute float vertexTileID;

uniform mat4 projection;

varying float tileID;
varying vec2 texCoord;

void main()
{
	tileID = vertexTileID;
	texCoord = vertexTexcoord;
    gl_Position = projection * vec4(vertexPosition, 1.0);
}
