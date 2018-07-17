#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


class Highscore
{
public:
	Highscore();									// Default constructor

	bool read();
	void calculate( string , int , string );
	void write();

	void draw( sf::RenderWindow* win );

	~Highscore();

protected:
	stringstream ss;
	ostringstream oss;

private:
	//Required
	vector<string> initials;
	vector<int> life;
	vector<string> time;
	vector<sf::Text> s_name;
	vector<sf::Text> s_time;
	vector<sf::Text> s_life;


	sf::Image i_hs;
	sf::Texture t_hs;
	sf::Sprite s_hs;

	sf::Font f;


};
#endif