#define MAX_TEXTURES 	4

// NEEDS TO BE CONVERTED INTO UNIFORM DATA!
#define TILE_SIZE 		16 	
#define NUM_TILES 		72.0f
#define NUM_COLS 		6.0f

uniform sampler2D u_texture;

varying float texID;
varying float tileID;
varying vec2 texCoord;

vec2 convertTileID(float in_tileID) {
	float numRows = NUM_TILES / NUM_COLS;
	float numCols = NUM_COLS;
	float xIndex = in_tileID - (numCols * floor(in_tileID / numCols));
	float yIndex = floor(in_tileID / numCols);
	float xOffset = xIndex * 1.0f / numCols;
	float yOffset = yIndex * 1.0f / numRows;
	float aspectX = numRows / numCols;
	float aspectY = numCols / numRows;
	return vec2(texCoord.x / numRows * aspectX + xOffset, texCoord.y / NUM_COLS * aspectY + yOffset);
}

void main()
{
	int textureID = int(texID);
    gl_FragColor = texture2D(u_texture, convertTileID(tileID));
}
