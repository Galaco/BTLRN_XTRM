#ifndef INPUTNAME_H
#define INPUTNAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

class InputName
{
public:
	InputName();									// Default constructor

	void draw( sf::RenderWindow* win );
	void update();

	std::string getName();

	void addChar( char );
	void deleteChar();

	~InputName();

protected:
	sf::Clock Clock;
	sf::Font f;


private:
	//Required
	sf::Texture t_bg;
	sf::Sprite s_bg;

	sf::Text char1;
	std::string name;
};
#endif