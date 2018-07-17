#include "lighting.h"


GLfloat lightpos[] = {0.5f, 40.f, 40.f, 0.45f};
GLfloat env[] = {0.2f,0.2f,0.2f};


Lighting::Lighting(){
	glShadeModel( GL_SMOOTH );


	glEnable(GL_LIGHT0);
	//glLightModelfv( GL_LIGHT_MODEL_AMBIENT , env);
	glLightfv(GL_LIGHT0, GL_AMBIENT, env);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

void Lighting::setPosition( float x , float y , int id ){

}

Lighting::~Lighting(){
}