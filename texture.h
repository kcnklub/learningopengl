#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
	// the texture id
	unsigned int ID;

	Texture(const char* texturePath, const unsigned int format);

};

#endif