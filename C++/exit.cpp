#include "Exit.h"

Exit::Exit(){
}


Exit::Exit( int x , int y ){								// OUR CONSTRUCTOR. Notice no default constructor 
	posX = x * 64.f;											// as there will be no given situation where
	posY = y * 64.f;
	gridX = x;
	gridY = y;
	velX = 0;
	velY = 0;
	rota = 0;
	rotb = 40;
	float sxmax = 0;
	float symax = 0;
	float sxmin = 0;
	float symin = 0;
	a_loader.loadObj( "resource/models/exit.obj" , vertices , indices , normals , texcoords );
	texture = a_loader.loadImage( "resource/materials/models/exit/galaxy.raw" );
	for( unsigned int i=0; i < vertices.size() ; ++i )
	{
		if( vertices[i] < sxmin ) { sxmin = vertices[i]; }
		if( vertices[i] > sxmax ) { sxmax = vertices[i]; }
		vertices[i] =  vertices[i];
		++i;
		if( vertices[i] < symin ) { symin = vertices[i]; }
		if( vertices[i] > symax ) { symax = vertices[i]; }
		vertices[i] =  vertices[i];
		++i;
	}
	sizeX = sxmax - sxmin;
	sizeY = symax - symin;
}


void Exit::draw() {											// DRAW OBJECT (basically each draw draws the array storing vertex information)		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDepthMask( false );
		glEnable( GL_TEXTURE_2D );
		glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
		glNormalPointer( GL_FLOAT, 0 , &normals[0] );
		glTexCoordPointer( 3 , GL_FLOAT , 0 , &texcoords[0] );

		glPushMatrix();
		glTranslatef(posX+32 , posY , 0 );
		glRotatef( rota , 0 , 0 , 1 );
		glTranslatef( -sizeX/2 , -sizeY/2 , 0 );
		glScalef( 1.5 , 1.5 , 1.5 );
		glBindTexture( GL_TEXTURE_2D , texture );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		glPopMatrix();
		glDisable( GL_TEXTURE_2D );
		glDepthMask( true );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);	
}


void Exit::update() {
	rota+=2.0;
	rotb+=1.5;
	if( rota > 360 ) rota = 0;
	if( rotb > 360 ) rotb = 0;
}