#include "menuButton.h"


MenuButton::MenuButton()
{
	f.loadFromFile( "resource/materials/fonts/pixel.ttf" );
	btnName.setFont( f );
	btnName.setColor( sf::Color( 150 , 150 , 255 ) );
	btnName.setCharacterSize( 24 );
	btnImg.loadFromFile( "resource/materials/gui/btn_main.png" );
	btnImg.createMaskFromColor( sf::Color ( 0 , 255 , 0 ) );
	btnImg.createMaskFromColor( sf::Color ( 255 , 255 , 255 , 128 ) );
	btnTex.loadFromImage( btnImg );
	btnSprt.setTexture( btnTex );
	btnSprt.setOrigin( (float)btnTex.getSize().x , (float)btnTex.getSize().y );

	Buffer.loadFromFile("resource/sound/button_click.ogg");
	Sound.setBuffer( Buffer );
}

MenuButton::MenuButton( std::string d )
{
	f.loadFromFile( "resource/materials/fonts/segoeui.ttf" );
	btnName.setString( d );
	btnName.setFont( f );
	btnName.setColor( sf::Color( 0 , 0 , 200 ) );
	btnName.setCharacterSize( 24 );
	btnImg.loadFromFile( "resource/materials/gui/btn_main.png" );
	btnImg.createMaskFromColor( sf::Color ( 0 , 255 , 0 ) );
	btnImg.createMaskFromColor( sf::Color ( 255 , 255 , 255 , 128 ) );
	btnTex.loadFromImage( btnImg );
	btnSprt.setTexture( btnTex );
	btnSprt.setOrigin( (float)btnTex.getSize().x , (float)btnTex.getSize().y );

	Buffer.loadFromFile("resource/sound/button_click.ogg");
	Sound.setBuffer( Buffer );
}

void MenuButton::draw( sf::RenderWindow* win )
{	
	win->draw( btnSprt );
	win->draw( btnName );
}

void MenuButton::press()
{
	Sound.play();
}

void MenuButton::update()
{

}

void MenuButton::setPosition( float x , float y )
{
	posX = x;
	posY = y;
	btnSprt.setPosition( x , y );
	btnName.setPosition( x - 240 , y - 48 );
}

void MenuButton::setMarked( bool d ){ isMarked = d; }

MenuButton::~MenuButton(){

}

float MenuButton::getPosY(){ return posY; }
float MenuButton::getPosX(){ return posX; }
void MenuButton::setText( std::string d ){ btnName.setString( d ); }