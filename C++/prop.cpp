#include "prop.h"

Prop::Prop(){
}


Prop::Prop( std::string d , std::string e, int x , int y , int z ){								// OUR CONSTRUCTOR. Notice no default constructor 
	char * f = (char*)e.c_str();
	posX = x + 0.f;											// as there will be no given situation where
	posY = y + 0.f;
	posZ = z + 0.f;
	a_loader.loadObj( d , vertices , indices , normals , texcoords );
	texture = a_loader.loadImage( f );
	for( unsigned int i=0; i < vertices.size() ; ++i )
	{
		vertices[i] =  vertices[i] + posX;
		++i;
		vertices[i] =  vertices[i] + posY;
		++i;
		vertices[i] =  vertices[i] + posZ;
	}
}


void Prop::draw() {											// DRAW OBJECT (basically each draw draws the array storing vertex information)		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glDepthMask( false );
		glEnable( GL_TEXTURE_2D );
		glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
		glNormalPointer( GL_FLOAT, 0 , &normals[0] );
		glTexCoordPointer( 3, GL_FLOAT, 0 , &texcoords[0] );

		glPushMatrix();
		glBindTexture( GL_TEXTURE_2D , texture );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		glPopMatrix();

		glDisable( GL_TEXTURE_2D );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);	
}

	
void Prop::setPosition( float f, float g , float h ) {				// SETS OBJECT POSITION VARIABLES
	posX = f;												// Set X position
	posY = g;												// Set y position
	posY = h;

	for ( unsigned int i = 0; i < vertices.size(); ++i )
	{
		vertices[i] = vertices[i] + f;
		++i;
		vertices[i] = vertices[i] + g;
		++i;
		vertices[i] = vertices[i] + h;
	}
}

// GETTERS AND SETTERS
float Prop::getPosZ(){ return posZ; }						// Return X Position