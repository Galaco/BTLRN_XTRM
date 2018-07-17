#include "player.h"


Player::Player(){
}

Player::Player( int x , int y ){
	dir = 1;
	state = "IDLE";
	frame = 0;
	posX = (float)x;
	posY = (float)y;		
	oldPosX = 0;
	oldPosY = 0;
	velX = 0;
	velY = 0;
	isAirBorn = false;
	isColliding = false;
	float sxmax = 0;
	float symax = 0;
	float sxmin = 0;
	float symin = 0;
	t_run[0] = a_loader.loadImage( "resource/materials/models/player/run_01.raw" );
	t_run[1] = a_loader.loadImage( "resource/materials/models/player/run_02.raw" );
	t_run[2] = a_loader.loadImage( "resource/materials/models/player/run_03.raw" );
	t_run[3] = a_loader.loadImage( "resource/materials/models/player/run_04.raw" );
	t_idle[0] = a_loader.loadImage( "resource/materials/models/player/idle_01.raw" );
	t_idle[1] = a_loader.loadImage( "resource/materials/models/player/idle_02.raw" );
	t_idle[2] = a_loader.loadImage( "resource/materials/models/player/idle_03.raw" );
	t_jump[0] = a_loader.loadImage( "resource/materials/models/player/jump_01.raw" );
	t_pound[0] = a_loader.loadImage( "resource/materials/models/player/pound_01.raw" );
	a_loader.loadObj( "resource/models/player.obj" , vertices , indices , normals , texcoords );
	for( unsigned int i=0; i < vertices.size(); ++i )
	{
		if( vertices[i] < sxmin ) { sxmin = vertices[i]; } else
		if( vertices[i] > sxmax ) { sxmax = vertices[i]; }
		++i;
		if( vertices[i] < symin ) { symin = vertices[i]; } else
		if( vertices[i] > symax ) { symax = vertices[i]; }
		++i;
	}
	sizeX = sxmax - sxmin;
	sizeY = symax - symin;

	BufferDeath.loadFromFile("resource/sound/death.ogg");
	BufferCollect.loadFromFile("resource/sound/jewel_collect.ogg");
}

void Player::jump( float d) {
	if ( oldVelY < velY ) isAirBorn = false;
	if ( ( velY < 2 && velY > -1 ) && ( isAirBorn == false ) ){  velY = d; /*state = "JUMP";*/	}	
	isAirBorn = true;
}

void Player::draw() {
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glDepthMask( false );
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable( GL_TEXTURE_2D );
	glVertexPointer( 3 , GL_FLOAT , 0 , &vertices[0] );
	glNormalPointer( GL_FLOAT, 0 , &normals[0] );
	glTexCoordPointer( 3 , GL_FLOAT, 0 , &texcoords[0] );
	
	glPushMatrix();
	if( state == "IDLE" ){ 
		if( dir == 1 ){
			glScalef( -1 , 1 , 1 ); posX+=32;
			glTranslatef( -posX , posY , 0 );
			glBindTexture( GL_TEXTURE_2D , t_idle[ animator.animateGL(frame , 3 ) ] );
			glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
			posX-=32;
		} else {
			glTranslatef( posX , posY , 0 );
			glBindTexture( GL_TEXTURE_2D , t_idle[ animator.animateGL(frame , 3 ) ] );
			glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		}
	} else
	if( state == "JUMP" ){
		glTranslatef( posX , posY , 0 );
		glBindTexture( GL_TEXTURE_2D , t_jump[ 0 ] );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
	} else
	if( state == "RUN" ) {
		if( dir == 1 ){ 
			glScalef( -1 , 1 , 1 ); posX+=32; 
			glTranslatef( -posX , posY , 0 );
			glBindTexture( GL_TEXTURE_2D , t_run[ animator.animateGL(frame , 4 ) ] ); 
			glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
			posX-=32;
		} else {
			glTranslatef( posX , posY , 0 );
			glBindTexture( GL_TEXTURE_2D , t_run[ animator.animateGL(frame , 4 ) ] ); 
			glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
		}
	} else
	if( state == "POUND" ){
		glTranslatef( posX , posY , 0 );
		glBindTexture( GL_TEXTURE_2D , t_pound[ 0 ] );
		glDrawArrays(GL_TRIANGLES, 0 , (GLsizei)vertices.size()/3 );
	}
	glPopMatrix();
	glDisable( GL_TEXTURE_2D );
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDepthMask( true );
	glDisableClientState( GL_NORMAL_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}

void Player::update() {
	oldPosX = posX;
	oldPosY = posY;
	if(velY>=0)
		posY += 6;
	else
	if(velY < 0 )
		posY += velY;
	posX += velX;
	if( oldPosY < posY && isAirBorn == false && state == "JUMP" ) state = "IDLE";

	if(velY < -4 && ( velY > -20 ) ) velY = -4;
	
	if( ( gridX * 64 ) + 64 < posX ) gridX++;
	if( gridX * 64 > posX ) gridX--;
	if( ( gridY * 64 ) + 64 < posY ) gridY++;
	if( gridY * 64 > posY ) gridY--;

	if( velY < -15 )
		state = "POUND";
	if( (velY > 4) || ( (velY < -1 ) && (velY > -4) ) )
		state = "JUMP";
}

void Player::move( char d ){
	switch( d )
	{
	case 'l':
		{
			if( state != "JUMP" ) state = "RUN";
			posX -= 3;
			//posX = posX + velX;
			break;
		}
	case 'r':
		{
			if( state != "JUMP" ) state = "RUN";
			posX += 3;
			//velX = velX + 0.5f;
			//posX = posX + velX;
			break;
		}
	}
	if( velX < -3 )
	{
		velX = -3;
	} else {
		if( velX > 3 ) velX = 3;
	}
}

void Player::pound(){
	if( velY < 0 ){
		velY = -20;
	}
}

void Player::playSound( std::string s ){
	if( s == "death" )
		Sound.setBuffer( BufferDeath );
	else
	if( s == "collect" )
		Sound.setBuffer( BufferCollect );

	Sound.play();
}

bool Player::airborn(){ return isAirBorn; }

Player::~Player(){
}