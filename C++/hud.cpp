#include "hud.h"


Hud::Hud(){
	str_lives = lives;
	f.loadFromFile("resource/materials/fonts/pixel.ttf" );
	state = "mainmenu";
	lives = 3;
	keys = 0;
	p_pound = false;
	keyPressed = 0;
	selPos = 0;
	selFrame = 0;
	oldSelFrame = 0;
	health = 10;
	i_m = 0;
	i_s = 0;
	i_ms = 0;
	pauseTime = 0;
	time=0;
	i_bg.loadFromFile("resource/materials/gui/title_bg.png");
	t_bg.loadFromImage( i_bg );
	s_bg.setTexture( t_bg );
	s_bg.setPosition( 0 , 0 );
	i_logo.loadFromFile("resource/materials/gui/logo.png");
	i_logo.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_logo.loadFromImage( i_logo );
	s_logo.setTexture( t_logo );
	i_sel.loadFromFile( "resource/materials/gui/hud_selector.png" );
	i_sel.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_sel.loadFromImage( i_sel );
	s_sel.setTexture( t_sel );
	i_pound.loadFromFile("resource/materials/gui/pound.png");
	i_pound.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_pound.loadFromImage( i_pound );
	s_pound.setTexture( t_pound );
	i_p_pickup.loadFromFile("resource/materials/gui/pound_instructions.png");
	i_p_pickup.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_p_pickup.loadFromImage( i_p_pickup );
	s_p_pickup.setTexture( t_p_pickup );
	play.setText( "Play");
	lvlSel.setText( "Highscores" );
	options.setText( "Options" );
	exit.setText( "Exit" );
	i_logo.loadFromFile("resource/materials/gui/logo.png");
	i_logo.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_logo.loadFromImage( i_logo );
	s_logo.setTexture( t_logo );
	i_sel.loadFromFile( "resource/materials/gui/hud_selector.png" );
	i_sel.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_sel.loadFromImage( i_sel );
	s_sel.setTexture( t_sel );
	s_bg.setPosition( 0 , 0 );
	s_lives.setColor( sf::Color( 255 , 255 , 255 ) );
	s_health.setColor( sf::Color( 255 , 255 , 255 ) );
	s_time.setColor( sf::Color( 255 , 255 , 255 ) );
	s_pause.setColor( sf::Color( 255 , 255 , 255 ) );
	s_keys.setColor( sf::Color( 255 , 255 , 255 ) );
	s_keys.setFont( f );
	s_health.setFont( f );
	s_lives.setFont( f );
	s_time.setFont( f );
	s_pause.setFont( f );
	s_pause.setString( "Paused. Press R to resume");
	i_bg.loadFromFile("resource/materials/gui/title_bg.png");
	t_bg.loadFromImage( i_bg );
	s_bg.setTexture( t_bg );
	i_UI.loadFromFile( "resource/materials/gui/hud_lower.png" );
	i_UI.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_UI.loadFromImage( i_UI );
	s_UI.setTexture( t_UI );

	BufferCollect.loadFromFile( "resource/sound/pickup.ogg" );
	BufferSel.loadFromFile( "resource/sound/select.ogg" );
	SoundCollect.setBuffer( BufferCollect );
	SoundSel.setBuffer( BufferSel );

	BufferMusic.loadFromFile( "resource/sound/menu.ogg" );
	SoundMusic.setBuffer( BufferMusic );
	SoundMusic.setVolume( 50 );
}

void Hud::addKeys( int i ){
	keys += i; 
}

void Hud::addScore( int d , bool e ){
	if ( e )
	{
		health = health + d;
	} else {
		health = d;
	}
}

void Hud::addLives( int d , bool e ){
	if ( e )
	{
		lives = lives + d;
	} else {
		lives = d;
	}
}

void Hud::addHealth( int d , bool e ){
	if ( e )
	{
		health = health + d;
	} else {
		health = d;
	}
}

void Hud::startup( sf::RenderWindow* win){
	if( state == "mainmenu")
	{	
		s_p_pickup.setPosition( (float)(win->getSize().x/2 )- i_p_pickup.getSize().x/2, (float)(win->getSize().y/2 )- i_p_pickup.getSize().y/2 );
		s_pound.setPosition( (float)(win->getSize().x - i_pound.getSize().x ) , (float)(win->getSize().y - i_pound.getSize().y ) );
		s_UI.setPosition( 0 , (float)(win->getSize().y - i_UI.getSize().y ) );
		s_lives.setCharacterSize( (win->getSize().y / 20) );
		s_health.setCharacterSize( (win->getSize().y / 20) );
		s_lives.setPosition( (float)(win->getSize().x/20) , (float)(win->getSize().y - ( win->getSize().y/40 ) * 6) );
		s_keys.setPosition( (float)(win->getSize().x/20)* 19 , (float)(win->getSize().y - ( win->getSize().y/40 ) * 6 ) );
		s_health.setPosition( (float)(win->getSize().x/20) , (float)(win->getSize().y - ( win->getSize().y/40 ) * 3) );
		s_time.setCharacterSize( (win->getSize().y / 20) );
		s_time.setPosition( (float)(( win->getSize().x/8 ) * 3) , (float)(win->getSize().y - ( win->getSize().y/40 ) * 3) );
		s_pause.setPosition( (float)(win->getSize().x/4) , (float)(win->getSize().y/2 ) );
		play.setPosition( (float)(win->getSize().x - win->getSize().x/2) , (float)(win->getSize().y - ( win->getSize().y/8 ) * 5 ));
		lvlSel.setPosition( (float)(win->getSize().x - win->getSize().x/2) , (float)(win->getSize().y - ( win->getSize().y/8 ) * 4) );
		options.setPosition( (float)(win->getSize().x - win->getSize().x/2) , (float)(win->getSize().y - ( win->getSize().y/8 ) * 3) );
		exit.setPosition( (float)(win->getSize().x - win->getSize().x/2) , (float)(win->getSize().y - ( win->getSize().y/8 ) * 2) );
		s_sel.setPosition( (float)(win->getSize().x - win->getSize().x/2) , exit.getPosY() - 64 );	
		s_logo.setPosition( (float)win->getSize().x/2 , 0 );
		

		keys = 0;
		p_pound = false;
		keyPressed = 0;
		selPos = 0;
		selFrame = 0;
		oldSelFrame = 0;
		health = 10;
		i_m = 0;
		i_s = 0;
		i_ms = 0;
		pauseTime = 0;
		time=0;
		if(lives == 0) lives = 3;
	    totalTime = 0;
	} else
	if( state == "play" )
	{
		i_m = 0;
		i_s = 0;
		i_ms = 0;
		str_m = "0";
		str_s = "0";
		str_ms = "0";
		if( time != 0 )totalTime += time;
		time=0;
		//p_pound = false;
		keys=0;
		if( health < 0 ) health = 10;
		Clock.restart();
	}
}

void Hud::draw( sf::RenderWindow* win )
{
	if( state == "mainmenu" )
	{
		win->draw(s_bg );
		win->draw( s_logo );
		win->draw( s_sel );
		play.draw( win );
		options.draw( win );
		exit.draw( win );
		lvlSel.draw( win );	
	} else
	if( state == "play" )
	{
		win->draw( s_UI );
		win->draw( s_health );
		win->draw( s_time );
		win->draw( s_lives );
		win->draw( s_keys );
		if(p_pound == true)
			win->draw( s_pound );
	} else
	if( state == "pause" )
	{
		win->draw( s_UI );
		win->draw( s_health );
		win->draw( s_time );
		win->draw( s_lives );
		win->draw( s_keys );
		win->draw( s_pause );
		if(p_pound == true)
			win->draw( s_pound );
	} 
	else
	if( state == "pickup" )
	{
		win->draw( s_UI );
		win->draw( s_health );
		win->draw( s_time );
		win->draw( s_lives );
		win->draw( s_keys );
		win->draw( s_p_pickup );
		if(p_pound == true)
			win->draw( s_pound );
	} else
	if( state == "inputname" )
	{
		win->draw(s_bg );
		playerName.draw( win );
	} else
	if( state == "scores" )
	{
		win->draw(s_bg );
		scores.draw( win );
	}
}

void Hud::update()
{
	if( state == "mainmenu" )
	{
		MusicStatus = SoundMusic.getStatus();
		if( MusicStatus != sf::Sound::Playing )
		{
			SoundMusic.play();
		}
		if( keyPressed == 1 )
		{
			switch( selPos )
			{
			case 3:
				{
					play.press();
					state = "play";
					SoundMusic.stop();
					keyPressed = 0;
					break;
				}
			case 2:
				{
					lvlSel.press();
					state = "scores";
					keyPressed = 0;
					break;
				}
			case 1:
				{
					options.press();
					keyPressed = 0;
					break;
				}
			case 0:
				{
					exit.press();
					state = "close";
					keyPressed = 0;
					break;
				}
			}
		}
		animator.animate2D( t_sel , s_sel , "LOOP" );
	} else
	if( state == "play" )
	{
		sf::Time c_time = Clock.getElapsedTime();
		time = (float)c_time.asMilliseconds() - pauseTime + totalTime;
		i_s = (int)time/1000;
		i_ms = ( time - i_s*1000 );
		if( i_s/60 > i_m )
		{
			++i_m;
			oss << i_m;
			str_m = oss.str();
			if( i_m < 10 ) str_m = "0" + oss.str();
			oss.str("");
		}
		i_s = i_s - ( 60 * i_m );
		oss << i_s;
		str_s = oss.str();
		if( i_s < 10 ) str_s = "0" + oss.str();
		oss.str("");
		oss << (int)i_ms;
		str_ms = oss.str();
		oss.str("");
		str_time = str_m + ':' + str_s + ':' + str_ms;
		s_time.setString( str_time );
		oss << health;
		str_health = oss.str();
		oss.str("");
		if( i_ms < i_msOld )
		{
			health = health - 2;
			s_health.setString( str_health );
		}
		i_msOld = i_ms;
		
		oss << lives;
		str_lives = oss.str();
		oss.str("");
		s_lives.setString( str_lives );

		oss << keys;
		str_keys = oss.str();
		oss.str("");
		s_keys.setString( str_keys );

		//endgame
		if( lives == 0 )
		{
			state = "inputname";
		}
	} else
	if( state == "pause" )
		saveTimer();
	else
	if( state == "pickup" )
	{
		if(p_pound == false)
			saveTimer();
	} else
	if( state == "calculate" )
	{
		name = playerName.getName();
		scores.calculate( name , health, str_time );
		state = "scores";
	}
}


void Hud::addChar( char c ){
	playerName.addChar( c );
}

void Hud::removeChar(){
	playerName.deleteChar();
}



void Hud::setSelPos( bool d ){ 
	if( selPos > 0 && d == 0)
	{
		SoundSel.play();
		selPos -= 1;
		s_sel.setPosition( s_sel.getPosition().x , s_sel.getPosition().y - ( play.getPosY() - lvlSel.getPosY() ) );
	}
	if( selPos < 3 && d == 1)
	{
		SoundSel.play();
		selPos += 1;
		s_sel.setPosition( s_sel.getPosition().x ,s_sel.getPosition().y + ( play.getPosY() - lvlSel.getPosY() ) );
	}
}

void Hud::saveTimer(){
	sf::Time c_time = Clock.getElapsedTime();
	pauseTime = (float)c_time.asMilliseconds() - time;
}

Hud::~Hud(){
}

std::string Hud::getState(){ return state; }
int Hud::getMarkerPos(){ return selPos; }
int Hud::getLives(){ return lives; }
int Hud::getHealth(){ return health; }
bool Hud::hasKey(){ if(keys>0)return true; else return false; }
bool Hud::hasPound(){ return p_pound; }
void Hud::setPressed( bool d ){ keyPressed = d; }
void Hud::setState( std::string d){ state = d; }

void Hud::grantPound(){
	p_pound = true;
	SoundCollect.play();
}