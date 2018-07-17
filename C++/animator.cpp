#include "animator.h"


Animator::Animator(){
	dir = 1;
}

void Animator::animate2D( sf::Texture& t , sf::Sprite& s , std::string r ){
	time = clock.getElapsedTime();
	if( time.asMilliseconds()/100 > 1.0F / 100 )
	{
		unsigned int x = s.getTextureRect().left + s.getTextureRect().width;
		if( r == "LOOP" )
		{	
			if( x >= t.getSize().x )
			{
				s.setTextureRect( sf::IntRect( 0 , 0 , 64 , 64 ) );
			} else {
				s.setTextureRect( sf::IntRect( s.getTextureRect().left + 64 , 0 , s.getTextureRect().width , 64 ) );
			}
		}
		if( r == "BOUNCE" )
		{
			//right
			if( x >= 1280 && dir == 1 )
			{
				s.setTextureRect( sf::IntRect( s.getTextureRect().left + 2 , 0 , s.getTextureRect().width , 640 ) );
				dir = 0;
			} else {
			if( dir == 1 ) s.setTextureRect( sf::IntRect( s.getTextureRect().left - 2 , 0 , s.getTextureRect().width , 640 ) );
			}
			//left
			if( x <= 0 && dir == 0 )
			{
				s.setTextureRect( sf::IntRect( s.getTextureRect().left - 2 , 0 , s.getTextureRect().width , 640 ) );
				dir = 1;
			} else {
			if( dir == 0 ) s.setTextureRect( sf::IntRect( s.getTextureRect().left + 2 , 0 , s.getTextureRect().width , 640 ) );
			}
		}
		clock.restart();
	}
}

int Animator::animateGL( int& d , int e ){
	time = clock.getElapsedTime();
	if( time.asMilliseconds()/100 > 1.F )
	{
		clock.restart();
		d = d + 1;
		if( d >= e ) d = 0;
		return d;
	} else { return d; }
}

Animator::~Animator(){
}