// NEEDS TO BE CONVERTED INTO UNIFORM DATA!
#define TILE_SIZE 		16 	
#define NUM_ROWS 		16.0f
#define NUM_COLS 		16.0f

uniform sampler2D font;

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
   vec4 font_texture = texture2D(font, convertTileID(tileID)); 

   if (font_texture.rgb == vec3(0.0,0.0,0.0))
      discard; 

    gl_FragColor = font_texture;
}
