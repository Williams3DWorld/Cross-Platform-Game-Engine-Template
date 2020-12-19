#define TEXTURE_SIZE 	512
#define TILE_SIZE 		64
#define NUM_ROWS 		8
#define MAX_TEXTURES 	4

uniform sampler2D u_textures[MAX_TEXTURES];

varying float texID;
varying float tileID;
varying vec2 texCoord;

vec2 convertTileID(float in_tileID) {
	float xIndex = in_tileID - (NUM_ROWS * floor(in_tileID / NUM_ROWS));
	float yIndex = floor(in_tileID / NUM_ROWS);
	float tileSizeNormalised = 1.0f / NUM_ROWS;
	float xOffset = xIndex * tileSizeNormalised;
	float yOffset = yIndex * tileSizeNormalised;

	return vec2(texCoord.x / NUM_ROWS + xOffset, texCoord.y / NUM_ROWS + yOffset);
}

void main()
{
	int textureID = int(texID);
    gl_FragColor = texture2D(u_textures[textureID], convertTileID(tileID));
}
