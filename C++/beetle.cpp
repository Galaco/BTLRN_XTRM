#include "Beetle.h"


Beetle::Beetle(){
}

Beetle::Beetle( int x , int y , int l , int r ){								// OUR CONSTRUCTOR. Notice no default constructor 
	posX = x * 64.f;											// as there will be no given situation where
	posY = ( y * 64.f ) - 32;
	min = l * 64;
	max = r * 64;
	velocity = 1;
	boost = false;
	frame = 0;
	dir = 0;
	velX = 0;
	velY = 0;
	gridX = x;
	gridY = y;
	float sxmax = 0;
	float symax = 0;
	float sxmin = 0;
	float symin = 0;
	t_run[0] = a_loader.loadImage( "resource/materials/models/beetle/run_01.raw" );
	t_run[1] = a_loader.loadImage( "resource/materials/models/beetle/run_02.raw" );
	t_run[2] = a_loader.loadImage( "resource/materials/models/beetle/run_03.raw" );
	t_run[3] = a_loader.loadImage( "resource/materials/models/beetle/run_04.raw" );
	a_loader.loadObj( "resource/models/beetle.obj" , vertices , indices , normals , texcoords );
	for( unsigned int i=0; i < vertices.size() ; ++i )
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
}

void Beetle::draw() {											// DRAW OBJECT (basically each draw draws the array storing vertex information)		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDepthMask( false );
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable( GL_TEXTURE_2D );

		glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
		glNormalPointer( GL_FLOAT, 0 , &normals[0] );
		glTexCoordPointer( 3 , GL_FLOAT, 0 , &texcoords[0] );

		glPushMatrix();
		glTranslatef( posX + velX, posY , 0 );
		if( dir == 1 ){ glScalef( -1 , 1 , 1 );posX-=64; }
		glBindTexture( GL_TEXTURE_2D , t_run[ animator.animateGL(frame , 3 ) ] ); 
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		glPopMatrix();
		if( dir == 1 ){ posX+=64; }
		glDisable( GL_TEXTURE_2D );
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDepthMask( true );
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);	
}

void Beetle::update() {
	oldPosX = posX;
	oldPosY = posY;

	if( dir == 0 ) posX -=velocity;
	if( dir == 1 ) posX +=velocity;

	if( posX + velX > max ){ dir = 0; }
	if( posX + velX < min ){ dir = 1; }

	if( ( gridX * 64 ) + 64 < posX + velX ){ gridX++; }
	if( gridX * 64 > posX + velX ){ gridX--; }
}

void Beetle::reverseDir(){
	if( dir == 0 )
		dir = 1;
	else
	if( dir == 1 ) 
		dir = 0;	
}


void Beetle::checkPlayerVis( float px , float py ){
	if( ( py < posX && dir == 0 ) || ( py > posX && dir == 1 ) )
		if( ( py >= posY-4 ) && ( py <= posY+sizeY ) )
		{
			if( boost == false ) velocity = velocity * 3;
			boost = true; 
		} else { 
			if ( boost == true ) velocity = velocity / 3;
			boost = false;
		}
}