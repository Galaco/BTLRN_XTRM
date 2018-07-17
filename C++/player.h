#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"


class Player : public Object
{
public:
	Player();							// Default Constructor. Will likely never be used
	Player( int , int );				// Constructor specifying the players inital location
	void move( char );					// Moves the object left and right
	void draw();
	void update();						// Performs calculations and draws the object
	void jump( float );					// Moves the player (jumping movement)
	bool airborn();
	void pound();
	void playSound( std::string );

	~Player();
					
	
protected:
	sf::SoundBuffer BufferDeath;
	sf::SoundBuffer BufferCollect;

private:
	bool isAirBorn;	
	GLuint t_run[6] , t_idle[3] , t_jump[3] , t_pound[3];


};
#endif