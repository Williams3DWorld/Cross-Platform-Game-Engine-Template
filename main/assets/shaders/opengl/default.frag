#define MAX_TEXTURES 	4

// NEEDS TO BE CONVERTED INTO UNIFORM DATA!
#define TILE_SIZE 		16 	
#define NUM_ROWS 		12.0f
#define NUM_COLS 		6.0f

uniform sampler2D u_textures[MAX_TEXTURES];

varying float texID;
varying float tileID;
varying vec2 texCoord;

vec2 convertTileID(float in_tileID) {
	float xIndex = in_tileID - (NUM_COLS * floor(in_tileID / NUM_COLS));
	float yIndex = floor(in_tileID / NUM_COLS);
	float xOffset = xIndex * 1.0f / NUM_COLS;
	float yOffset = yIndex * 1.0f / NUM_ROWS;

	float numRows = NUM_ROWS;
	float numCols = NUM_COLS;

	float aspectX = numRows / numCols;
	float aspectY = numCols / numRows;

	return vec2(texCoord.x / NUM_ROWS * aspectX + xOffset, texCoord.y / NUM_COLS * aspectY + yOffset);
}

void main()
{
	int textureID = int(texID);
    gl_FragColor = texture2D(u_textures[textureID], convertTileID(tileID));
}
