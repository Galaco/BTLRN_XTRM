#include "wall.h"


Wall::Wall(){
}


Wall::Wall( std::string d , std::string e , std::string t , int x , int y ){								// OUR CONSTRUCTOR. Notice no default constructor 
	char * f = (char*)e.c_str();
	posX = x * 64.f;											// as there will be no given situation where
	posY = y * 64.f;
	gridX = x;
	gridY = y;
	velX = 0;
	velY = 0;
	float sxmax = 0;
	float symax = 0;
	float sxmin = 2000;
	float symin = 2000;
	type = 'n';
	if(t == "p") type = 'p'; else
	if(t == "f") type = 'f';
	a_loader.loadObj( d , vertices , indices , normals , texcoords );
	texture = a_loader.loadImage( f );
	for( unsigned int i=0; i < vertices.size(); ++i )
	{
		if( vertices[i] < sxmin ) { sxmin = vertices[i]; }
		if( vertices[i] > sxmax ) { sxmax = vertices[i]; }
		vertices[i] =  vertices[i] + posX;
		++i;
		if( vertices[i] < symin ) { symin = vertices[i]; }
		if( vertices[i] > symax ) { symax = vertices[i]; }
		vertices[i] =  vertices[i] + posY;
		++i;
	}
	sizeX = sxmax - sxmin;
	sizeY = symax - symin;
}

char Wall::getType(){ return type; }