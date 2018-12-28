#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#ifdef __APPLE__
	#include <OpenGL/glu.h>
	#include <OpenGL/gl.h>
#endif
#include <iostream>
#include <fstream>
#include <string>

#include "assetLoader.h"
#include "animator.h"

class Object
{
public:
	Object();
	Object( int , int );		// our constructor. arguments are x,y
	void draw();				// draws the object
	void update();

	void playSound();

	virtual ~Object();

	// GETTERS
	float getPosX();				// returns X position
	float getPosY();				// returns Y position
	float getOldPosX();
	float getOldPosY();
	int getGridX();
	int getGridY();
	float getSizeX();
	float getSizeY();
	float getVelX();				// returns X velocity
	float getOldVelX();			// returns X velocity in previous frame
	float getVelY();				// returns y velocity
	float getOldVelY();			// returns Y velocity in previous frame
	bool getCollision();				// returns whether object is colliding
	// SETTERS 
	void setVelX( float );			// sets X velocity
	void setVelY( float );			// sets Y velocity
	void setCollision( bool );			// sets boolean that states whether object is colliding
	void setPosX( float );
	void setPosY( float );
	void setGridX( int );
	void setGridY( int );
	void setDir( bool );
	void setState( std::string );
	
protected:
	// Setup model information
	float posX , posY , oldPosX , oldPosY , sizeX , sizeY;
	int gridX , gridY;
	float oldVelY , velY , oldVelX , velX;					// Additional values required but that may not be whole numbers
	bool isColliding , dir;		//dir 1 is right
	std::string state;

	sf::SoundBuffer Buffer;
	sf::Sound Sound;

	AssetLoader a_loader;
	Animator animator;
	std::vector<GLfloat> vertices;
	std::vector<GLushort> indices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	GLuint texture;
	int frame;

private:
};
#endif