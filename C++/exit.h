#ifndef EXIT_H
#define EXIT_H

#include "object.h"

class Exit : public Object
{
public:
	Exit();
	Exit( int , int );		// our constructor. arguments are x,y
	void draw();							// draws the object
	void update();


protected:


private:
	float rota, rotb;
};
#endif