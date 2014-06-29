#ifndef TEXTURE_H
#define TExTURE_H

#ifdef _WIN32
	#define WIN32_LEAN_MEAN
	#include <windows.h>
#endif

#if defined (_APPLE_) && defined(_MACH_)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <gl/GL.h>
	#include <gl/GLU.h>
#endif

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

//typedef	struct									
//{
//	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
//	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
//	GLuint	width;											// Image Width
//	GLuint	height;											// Image Height
//	GLuint	texID;											// Texture ID Used To Select A Texture
//	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
//} Texture;	

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;

typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

class Texture
{
public:
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;
	TGAHeader tgaheader;									// TGA header
	TGA tga;
	GLubyte uTGAcompare[12];	// Uncompressed TGA Header
	GLubyte cTGAcompare[12];

	string name;

	static vector<Texture *> textures;
private:
	bool LoadTGA(char * filename);
	bool createTexture(unsigned char *imageData, int width, int height, int type);
	bool LoadUncompressedTGA(char *, FILE *);	// Load an Uncompressed file
	bool LoadCompressedTGA(char *, FILE *);

public:
	Texture(char* filename, string name = "");
	~Texture(void);
};

#endif