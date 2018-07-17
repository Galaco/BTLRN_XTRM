#include "physics.h"


Physics::Physics(){
	f_gravity = 1;
	f_friction = 1;
}

Physics::Physics( float f , float g ){
	f_gravity = g;
	f_friction = f;
}

float Physics::gravity( float d ){
	if( d > -11) --d;
	return d;
}

float Physics::friction( float d ){
	if( !( d == 0 ) )
	{
		if( d > 0 ) d = d - ( 0.25f );
		if( d < 0 ) d = d + ( 0.25f );
	}
	return d;
}

bool Physics::checkGrid( Object* a , Object* b ){
	if( ( a->getGridX() == b->getGridX() ) || ( a->getGridX() == b->getGridX() + 1 ) || ( a->getGridX() == b->getGridX() - 1 ) )
	{ if( ( a->getGridY() == b->getGridY() ) || ( a->getGridY() == b->getGridY() + 1 ) || ( a->getGridY() == b->getGridY() - 1 ) )
		{ return true; } else { return false; }
	} else { return false; }
}

char Physics::checkAABB( Object* a , Object* b ){
	char col;
	col = 'n';

	if( !( ( ( a->getPosX() + a->getSizeX() + a->getVelX() < b->getPosX() ) ||
		   ( b->getPosX() + b->getSizeX() + b->getVelX() < a->getPosX() ) ) ||
		   ( ( a->getPosY() + a->getSizeY() + a->getVelY() < b->getPosY() ) ||
		   ( b->getPosY() + b->getSizeY() + b->getVelY() < a->getPosY() ) ) ) ) {
		float du , dr , dl , dd;
		du = abs( ( b->getPosY() + b->getSizeY() + b->getVelY() ) - a->getPosY() );
		dd = abs( ( a->getPosY() + a->getSizeY() + a->getVelY() ) - b->getPosY() );
		dr = abs( ( b->getPosX() + b->getSizeX() + b->getVelX() ) - a->getPosX() );
		dl = abs( ( a->getPosX() + a->getSizeX() + a->getVelX() ) - b->getPosX() );
		if( du <= dd && du <= dr && du <= dl ) col = 'u'; else
		if( dd <= du && dd <= dr && dd <= dl ) col = 'd'; else
		if( dl <= dd && dl <= dr && dl <= du ) col = 'l'; else
		if( dr <= dd && dr <= du && dr <= dl ) col = 'r';
	}

	return col;
}

sf::IntRect Physics::getAABB( Object* o ){
	sf::Vector2f pos(o->getPosX() , o->getPosY() );
	sf::Vector2f size(o->getSizeX() , o->getSizeY() );

	return sf::IntRect( static_cast<int> ( pos.x ),
						static_cast<int> ( pos.y ),
						static_cast<int> ( pos.x + size.x ),
						static_cast<int> ( pos.y + size.y ) );
}

Physics::~Physics(){
}