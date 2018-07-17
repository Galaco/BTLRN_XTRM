#include "settings.h"


Settings::Settings(){
	width = 640;
	height = 640;
	antialiasing = 0;
	volume = 100;
}

bool Settings::read(){
	std::ifstream f;
	std::string d;
	std::string holder;
	f.open( "resource/cfg/game.cfg" );
	if( ! ( f.is_open() ) )
	{
		std::cout << "cfg not found. Using default settings" << std::endl;
		return false;
	}
	while( f >> holder )
	{
		if( ( holder == "#" ) || ( holder == "g" ) )
			getline(f , d , '\n' );
		else
		if( holder == "width" )
			f >> width;
		else
		if( holder == "height" )
			f >> height;
		else
		if( holder == "antialiasing" )
			f >> antialiasing;
		else
		if( holder == "volume" )
			f >> volume;
		else
		if( holder == "verticalsync" )
			f >> verticalsync;
	}
	f.close();
	return true;
}

bool write(){
	return true;
}



int Settings::getWidth(){ return width; }
int Settings::getHeight(){ return height; }
int Settings::getVolume(){ return volume; }
int Settings::getAA() { return antialiasing; }
bool Settings::getVsync(){ return verticalsync; }

Settings::~Settings(){
}