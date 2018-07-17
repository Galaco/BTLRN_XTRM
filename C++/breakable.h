#ifndef BREAKABLE_H
#define BREAKABLE_H

#include "object.h"

class Breakable : public Object
{
public:
	Breakable();
	Breakable( int , int );
	void draw();							// draws the object

protected:


private:
};
#endif