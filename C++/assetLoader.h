//*******************************************************************
// All encompassing class for loading openGL assets
// Support for: .obj objects
// Support for: .raw textures
//*******************************************************************

#ifndef ASSETLOADER_H
#define ASSETLOADER_H
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cmath>

using namespace std;

class AssetLoader {
public:
	AssetLoader();

	bool loadObj( std::string , std::vector<GLfloat>& , std::vector<GLushort>&, std::vector<GLfloat>& , std::vector<GLfloat>& ); // load .obj
	GLuint loadImage( const char * );	// laods and creates a texture

	void deleteTex();
	~AssetLoader();

protected:

private:
	GLuint loadSFMLImage( const char * );	// loads and generates a texture from sf::Image supported formats
	GLuint loadRaw( const char * );			// loads and generates a texture directly from the .raw format
	
	
	GLuint texture;

	sf::Image image;
};
#endif