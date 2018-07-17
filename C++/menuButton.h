#ifndef SONGBUTTON_H
#define SONGBUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>


class MenuButton
{

public:
	MenuButton();
	MenuButton( std::string );

	void draw( sf::RenderWindow* win );
	void setPosition( float , float );
	void update();
	void press();

	float getPosX();
	float getPosY();
	void setMarked( bool );
	void setText( std::string );

	~MenuButton();


private:
	sf::Image btnImg;
	sf::Texture btnTex;
	sf::Sprite btnSprt;
	sf::Text btnName;
	sf::Font f;

	sf::SoundBuffer Buffer;
	sf::Sound Sound;


	bool isMarked;
	float posX , posY;
}; 
#endif