#ifndef DOOR_H
#define DOOR_H

#include "object.h"

class Door : public Object
{
public:
	Door();
	Door( int , int );
	void draw();							// draws the object
	bool open( bool );
	void update();
protected:


private:
	bool isOpening;
	int openDist;
};
#endif