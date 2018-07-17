#ifndef WORLDSPAWN_H
#define WORLDSPAWN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "wall.h"
#include "jewel.h"
#include "prop.h"
#include "exit.h"
#include "beetle.h"
#include "key.h"
#include "door.h"
#include "breakable.h"

using namespace std;

class WorldSpawn
{
public:
	// Constructors
	WorldSpawn();
	bool build( vector<Wall*>& , vector<Jewel*>& , vector<Beetle*>& , vector<Key*>& , vector<Door*>& , vector<Breakable*>& , Player*& , Exit*& , vector<Prop*>& , sf::RenderWindow* , string );	// Creates our world
	void draw( vector<Wall*>& , vector<Jewel*>& , vector<Beetle*>& , vector<Key*>& , vector<Door*>& , vector<Breakable*>& , Player*& , Exit*& , vector<Prop*>& );	// Draws our world
	bool clean( vector<Wall*>& , vector<Jewel*>& , vector<Beetle*>& , vector<Key*>& , vector<Door*>& , vector<Breakable*>& , Player*& , Exit*& , vector<Prop*>& , string& , int& );	// Deletes our world
	
	
	void loadScreen( sf::RenderWindow* );
	void percentage( float );
	
	// Getters
	int getSizeX();			// returns world size X
	int getSizeY();			// returns world sizy Y

	~WorldSpawn();

protected:
	ostringstream oss;

private:
	// LEVEL SETUP INFORMATION
	string objectType;
	char o_In [3];
	int objectX , objectY , objectZ , sizeX , sizeY , o_count;
	float pcent;
	bool ready;

	//Level variables
	bool s_jewel;


	// Loading screen
	sf::Image i_lvl , i_ctrl;
	sf::Texture t_lvl , t_ctrl;
	sf::Sprite s_lvl , s_ctrl;
	sf::RectangleShape l_bar;
	sf::Text s_ready;
};
#endif