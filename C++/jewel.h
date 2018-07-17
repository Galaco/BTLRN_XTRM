#ifndef JEWEL_H
#define JEWEL_H

#include "object.h"

class Jewel : public Object
{
public:
	Jewel( std::string , std::string , int , int , int );		// our constructor. arguments are x,y
	void draw();							// draws the object
	void update();

	bool getSpecial();

protected:


private:
	int bobdir;
	float rotation , bob;
	bool s_jewel;
};
#endif