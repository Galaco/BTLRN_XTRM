#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "lighting.h"
#include "worldSpawn.h"
#include "hud.h"
#include "physics.h"
#include "camera.h"
#include "player.h"
#include "jewel.h"
#include "beetle.h"
#include "prop.h"
#include "exit.h"
#include "key.h"
#include "door.h"
#include "breakable.h"

using namespace std;

const int FRAMERATE=60;				// the number of updates per second

class Game
{
public:
	Game( sf::RenderWindow* );
	Game();							// default constructor - good practice to always include
	
	void init();					// access resource
	void draw();					// draws the game frame
	void getInput();				// gets the input from user
	void update();					// takes care of any updating
	void play();

	~Game();						// destructor

protected:
	//required for all
	sf::RenderWindow* win;			// a pointer to the window to draw to
	unsigned int width;				// the original window size - width
	unsigned int height;			// the original window size - height
	sf::Clock Clock;				// for timing the movement
	sf::Time t_Clock;


private:
	//game specifics
	int level , lvlX , lvlY;
	string levelLocation , state;
	bool canPress;


	WorldSpawn world;				// the world
	Hud hud;						// the HUD
	Camera camera;				// the Camera
	Physics physics;				// the Physics Calculator
	Lighting lighting;

	vector<Jewel*> jewel;
	vector<Wall*> wall;
	vector<Beetle*> beetle;
	vector<Prop*> prop;
	vector<Key*> key;
	vector<Door*> door;
	vector<Breakable*> breakable;
	Player * player;				// the Player
	Exit * exit;
};
#endif