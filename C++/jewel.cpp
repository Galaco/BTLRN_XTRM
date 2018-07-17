#include "jewel.h"


Jewel::Jewel( std::string f , std::string img , int x , int y , int special ){								// OUR CONSTRUCTOR. Notice no default constructor 
	posX = x * 64.f;											// as there will be no given situation where
	posY = y * 64.f;
	gridX = x;
	gridY = y;
	velX = 0;
	velY = 0;
	float sxmax = 0;
	float symax = 0;
	float sxmin = 2000;
	float symin = 2000;
	if( special == 1 )
		s_jewel = true;
	 else
		s_jewel = false;
	texture = a_loader.loadImage( img.c_str() );
	a_loader.loadObj( f , vertices , indices , normals , texcoords );
	for( unsigned int i=0; i < vertices.size(); ++i )
	{
		if( vertices[i] < sxmin ) { sxmin = vertices[i]; }
		if( vertices[i] > sxmax ) { sxmax = vertices[i]; }
		++i;
		if( vertices[i] < symin ) { symin = vertices[i]; }
		if( vertices[i] > symax ) { symax = vertices[i]; }
		++i;
	}
	sizeX = sxmax - sxmin;
	sizeY = symax - symin;
	rotation = 0;
	bob = 0;
	bobdir = 1;
}

void Jewel::draw() {											// DRAW OBJECT (basically each draw draws the array storing vertex information)		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnable( GL_TEXTURE_2D );
		glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
		glNormalPointer( GL_FLOAT, 0 , &normals[0] );
		glTexCoordPointer( 3 , GL_FLOAT, 0 , &texcoords[0] );

		glPushMatrix();
		glColor3f( 0.1f , 0.25f , 0.7f );
		glTranslatef( posX + 32 , posY + bob , 0 );
		glRotatef( rotation , 0 , 1 , 0 );
		glTranslatef( -sizeX/2 , 0 , 0 );
		glBindTexture( GL_TEXTURE_2D , texture );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );

		glPopMatrix();
		glDisable( GL_TEXTURE_2D );
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);	
}

void Jewel::update() {
	// rotation
	if( rotation < 360 )
	{
		rotation = rotation + 1;
	} else {
		rotation = 1;
	}
	// bob
	if( ( bob == 8 ) || ( bob == -8 ) )
	{
		bobdir = bobdir * -1;
	}
	if( bobdir == 1 )
	{
		bob = bob + 0.5f;
	} else {
		bob = bob - 0.5f;
	}
}

bool Jewel::getSpecial(){ return s_jewel; }