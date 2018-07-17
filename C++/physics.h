#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "object.h"

class Physics
{
public:	
	Physics();								// Default Constructor
	Physics( float , float );				// Constructor allows us to set a gravity value
	float gravity( float );						// Performs gravity on an input velocity
	float friction( float );						// Performs friction on an input velocity
	bool checkGrid( Object* , Object* );
	char checkAABB( Object* , Object* );

	~Physics();

protected:


private:
	//Required
	float f_gravity , f_friction;

	sf::IntRect getAABB( Object* );
};
#endif