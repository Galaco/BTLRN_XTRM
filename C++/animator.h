#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Animator
{
public:	
	Animator();
	void animate2D( sf::Texture& , sf::Sprite& , std::string );
	void animate( std::vector<GLfloat>& );
	void animateSkeletal(); // Not used
	int animateGL( int& , int );

	~Animator();

protected:
	sf::Clock clock;
	sf::Time time;

private:
	int frame;
	bool dir;

};
#endif