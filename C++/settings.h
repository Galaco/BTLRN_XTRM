#ifndef SETTINGS_H
#define SETTINGS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

class Settings {
public:
	Settings();
	bool read();
	bool write();

	int getWidth();
	int getHeight();
	int getVolume();
	int getAA();
	bool getVsync();

	~Settings();


protected:


private:
	int width , height;
	int volume , antialiasing;
	bool verticalsync;
};
#endif