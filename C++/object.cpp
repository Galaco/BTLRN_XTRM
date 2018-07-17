#include "Object.h"


Object::Object(){
	posX = 0;
	posY = 0;
	oldPosX = 0;
	oldPosY = 0;
	gridX = 0;
	gridY = 0;
	//a_loader = NULL;
}


Object::Object( int x , int y ){							// OUR CONSTRUCTOR. Notice no default constructor 
	posX = x + 0.f;											// as there will be no given situation where
	posY = y + 0.f;											// an object will be created without initial coordinates
	oldPosX = 0;
	oldPosY = 0;
	gridX = 0;
	gridY = 0;
	velX = 0;
	velY = 0;
}


void Object::draw() {											// DRAW OBJECT (basically each draw draws the array storing vertex information)		
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable( GL_TEXTURE_2D );
		glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
		glNormalPointer( GL_FLOAT, 0 , &normals[0] );
		glTexCoordPointer( 3 , GL_FLOAT, 0 , &texcoords[0] );

		glPushMatrix();
		glBindTexture( GL_TEXTURE_2D , texture );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		glPopMatrix();

		glDisable( GL_TEXTURE_2D );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );	
}

void Object::update() {
	oldPosX = posX;
	oldPosY = posY;
}

void Object::playSound() {
	Sound.play();
}

	
// SETTERS
void Object::setPosX( float x ){ posX = x; }
void Object::setPosY( float y ){ posY = y; }
void Object::setGridX( int d ){gridX = d; }
void Object::setGridY( int d ){gridY = d; }
void Object::setVelX( float d){ oldVelX = velX; velX = d; }
void Object::setVelY( float d){ oldVelY = velY; velY = d; }
void Object::setCollision( bool d){ isColliding = d; }
// GETTERS
float Object::getPosX(){ return posX; }						// Return X Position
float Object::getPosY(){ return posY; }						// Return Y position
float Object::getOldPosX(){ return oldPosX; }
float Object::getOldPosY(){ return oldPosY; } 
int Object::getGridX(){ return gridX; }
int Object::getGridY(){ return gridY; }
float Object::getSizeX(){ return sizeX; }
float Object::getSizeY(){ return sizeY; } 
float Object::getVelX(){ return velX; }
float Object::getVelY(){ return velY; }
float Object::getOldVelX(){ return oldVelX; }
float Object::getOldVelY(){ return oldVelY; }
bool Object::getCollision(){ return isColliding; }
void Object::setDir( bool d ){ dir = d;  }
void Object::setState( std::string d){ state = d; }


Object::~Object(){
	vertices.clear();
	indices.clear();
	normals.clear();
	texcoords.clear();
	//delete a_loader;
}