#include "inputName.h"


InputName::InputName(){
	f.loadFromFile("resource/materials/fonts/pixel.ttf" );
	char1.setColor( sf::Color( 255 , 255 , 255 ) );
	char1.setCharacterSize( 160 );
	char1.setPosition( 160 , 256 );
	char1.setFont( f );

	name = "";
	char1.setString( "" );
	t_bg.loadFromFile("resource/materials/gui/inputname.png" );
	s_bg.setTexture( t_bg );

}

void InputName::draw( sf::RenderWindow* win )
{
	win->draw( s_bg );
	win->draw( char1 );
}


void InputName::update()
{
}

std::string InputName::getName(){
	return name;
}

void InputName::deleteChar(){
	if( name.size() > 0 ){
		//name.erase( name.begin() + (name.size()-1) );
			name.pop_back();
			char1.setString( name );
	}
}

void InputName::addChar( char c ){
	if( name.size() < 3){
		name += c;
		char1.setString( name );
	}
}

InputName::~InputName(){
}