#include "highscores.h"


Highscore::Highscore(){
	t_hs.loadFromFile("resource/materials/gui/highscores.png");
	s_hs.setTexture( t_hs );

	f.loadFromFile( "resource/materials/fonts/pixel.ttf" );
	if( !read() )
	{
		initials.push_back( "AAA" );
		initials.push_back( "BBB" );
		initials.push_back( "CCC" );
		initials.push_back( "DDD" );
		initials.push_back( "EEE" );
		initials.push_back( "FFF" );
		initials.push_back( "GGG" );
		initials.push_back( "HHH" );
		initials.push_back( "NUL" );

		life.push_back( 40 );
		life.push_back( 35 );
		life.push_back( 30 );
		life.push_back( 25 );
		life.push_back( 20 );
		life.push_back( 15 );
		life.push_back( 10 );
		life.push_back( 05 );
		life.push_back( 00 );

		time.push_back( "00:15:00" );
		time.push_back( "00:30:00" );
		time.push_back( "00:45:00" );
		time.push_back( "01:00:00" );
		time.push_back( "01:15:00" );
		time.push_back( "01:30:00" );
		time.push_back( "02:00:00" );
		time.push_back( "03:59:99" );
		time.push_back( "null" );
	}

	for( int i = 0; i < 9; ++i )
	{
		s_life.push_back( sf::Text( " " , f , 32 ) );
		s_name.push_back( sf::Text( " " , f , 32 ) );
		s_time.push_back( sf::Text( " " , f , 32 ) );

		oss << life[i];
		/*if(life[i] < 10 )
			s_score[i].setString( " 0" + oss.str());
		else*/
		s_life[i].setString( oss.str());
		oss.str("");
		

		s_name[i].setString( initials[i] );
		s_time[i].setString( time[i] );

		s_name[i].setFillColor( sf::Color( 224 , 224 , 224 ) );
		s_time[i].setFillColor( sf::Color( 224 , 224 , 224 ) );
		s_life[i].setFillColor( sf::Color( 224 , 224 , 224 ) );
		s_life[i].setPosition( 300 , 140+ (i+1)*40.f );
		s_name[i].setPosition( 112 , 140+ (i+1)*40.f );
		s_time[i].setPosition( 440 , 140+ (i+1)*40.f );
	}
}

bool Highscore::read(){
	ifstream f;
	string i;
	int j;
	f.open( "resource/cfg/highscores.hsf" );
	if( !(f.is_open() ) )
	{
		cout << "no highscore table found. Using default" << endl;
		return false;
	} else {
		initials.clear();
		time.clear();
		life.clear();
		while( !f.eof() )
		{
			getline(f , i , '\n' );
			initials.push_back( i );

			getline(f , i , '\n' );
			j = atoi(i.c_str() );
			life.push_back( j );

			getline(f , i , '\n');
			time.push_back( i );	
		}

		initials.push_back( "null" );
		life.push_back( 0 );
		time.push_back( "null" );
	}

	f.close();
	return true;
}

void Highscore::calculate( std::string n , int hp , std::string t ){
	for( int i = 7; i > -1; --i )
	{
		if(hp > life[i]){
		
			initials[i+1] = initials[i];
			life[i+1] = life[i];
			time[i+1] = time[i];
			
			s_name[i+1].setString( initials[i] );
			oss.str("");
			oss << life[i+1];
			s_life[i+1].setString( oss.str() );
			s_time[i+1].setString( time[i] );

			initials[i] = n;
			life[i] = hp;
			time[i] = t;


			s_name[i].setString( initials[i] );
			oss.str("");
			oss << life[i];
			s_life[i].setString( oss.str() );
			s_time[i].setString( time[i] );
		}
	}
	for( int i = 7; i > -1; --i )
	{
		s_name[i].setString( initials[i] );
		oss.str("");
		oss << life[i];
		s_life[i].setString( oss.str() );
		s_time[1].setString( time[i] );
	}

	write();
}


void Highscore::write(){
	ofstream o;
	o.open( "resource/cfg/highscores.hsf" );

	for( unsigned int i = 0; i < 8; ++i )
	{
		o << initials[i] << "\n";
		o << life[i] << "\n";
		o << time[i] << "\n";
	}
	o << "null" << "\n";
	o << 0 << "\n";
	o << "null" << "\n";

	o.close();
}

void Highscore::draw( sf::RenderWindow* win ){
	win->draw(s_hs);
	for( int i=0; i<8; ++i )
	{
		win->draw( s_life[i] );
		win->draw( s_name[i] );
		win->draw( s_time[i] );
	}
}

Highscore::~Highscore(){
}