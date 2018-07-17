#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "menuButton.h"
#include "animator.h"
#include "highscores.h"
#include "inputName.h"


class Hud
{
public:
	Hud( );									// Default constructor

	void addScore( int , bool );			// Add score
	void addLives( int , bool );			// Add lives/reset lives if bool = true
	void addHealth( int , bool );			// Add health/set to int if bool = true
	void addKeys( int i );
	void startup( sf::RenderWindow* );
	void draw( sf::RenderWindow* win );
	void update();

	std::string getState();
	int getMarkerPos();
	int getLives();
	int getHealth();
	bool hasKey();
	bool hasPound();
	void grantPound();
	void setPressed( bool );
	void setSelPos( bool );
	void setState( std::string );
	void saveTimer();


	void addChar( char );
	void removeChar();

	~Hud();

protected:
	sf::Clock Clock;
	std::ostringstream oss;
	sf::Font f;

private:
	//Required
	int lives , selPos, selFrame, oldSelFrame , health, keys;
	bool keyPressed, p_pound;
	float pauseTime, totalTime;
	std::string state;

	sf::SoundBuffer BufferCollect , BufferSel , BufferMusic;
	sf::Sound SoundCollect , SoundSel , SoundMusic;
	sf::Sound::Status MusicStatus;

	Highscore scores;
	MenuButton play;
	MenuButton lvlSel;
	MenuButton options;
	MenuButton exit;
	Animator animator;
	InputName playerName;

	std::string name;

	sf::Image i_bg , i_sel , i_logo, i_UI, i_pound , i_p_pickup;
	sf::Texture t_bg , t_sel , t_logo , t_UI , t_pound , t_p_pickup;
	sf::Sprite s_bg , s_sel , s_logo , s_UI , s_pound , s_p_pickup;

	//Below are varables required for showing the time
	float time;
	sf::Text s_health , s_time , s_pause, s_lives, s_keys;
	std::string str_time , str_m , str_s , str_ms , str_health, str_lives, str_keys;
	int i_s , i_m;
	double i_ms , i_msOld;
};
#endif