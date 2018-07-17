#ifndef WALL_H
#define WALL_H

#include "object.h"

class Wall : public Object
{
public:
	Wall();
	Wall( std::string , std::string , std::string , int , int );		// our constructor. arguments are x,y
	
	char getType();

protected:
	char type;

private:
};
#endif