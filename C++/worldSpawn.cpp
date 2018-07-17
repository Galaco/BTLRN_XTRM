#include "worldSpawn.h"


WorldSpawn::WorldSpawn(){
	o_count = 0;
	pcent = 0;
	ready = 0;
	i_ctrl.loadFromFile( "resource/materials/gui/controls.png" );
	i_ctrl.createMaskFromColor( sf::Color( 0 , 255 , 0 ) );
	t_ctrl.loadFromImage( i_ctrl );
	s_ctrl.setTexture( t_ctrl );
	s_ready.setString( "Press Spacebar to Play" );
	s_ready.setColor( sf::Color( 0 , 0 , 0 ) );
	s_jewel = false;
	s_lvl.setPosition( 0 , 0 );	
	s_ready.setPosition( 100 , 500 );
}

bool WorldSpawn::build( vector<Wall*>& w , vector<Jewel*>& j , vector<Beetle*>& b , vector<Key*>& k , vector<Door*>& door, vector<Breakable*>& breakable , Player*& p , Exit*& e , vector<Prop*>& prop , sf::RenderWindow* win , string d ) {
	s_ctrl.setPosition( (float)( win->getSize().x - t_ctrl.getSize().x ) , 0 );

	ifstream levelFile;
	string mod , tex , type;
	int i_var[9];
	levelFile.open( d );
	if ( !(levelFile.is_open() ) ) { return false; }	
	while( objectType != "count" )
	{
		levelFile >> objectType;
	}
	levelFile >> o_In;		
	o_count = atoi ( o_In );
	levelFile >> tex;
	i_lvl.loadFromFile( tex );
	t_lvl.loadFromImage( i_lvl );
	s_lvl.setTexture( t_lvl );

	while ( levelFile >> objectType )
	{
		levelFile >> o_In;		
		objectX = atoi ( o_In );
		levelFile >> o_In;		
		objectY = atoi ( o_In );
		if( objectType == "#" )
		{
			getline(levelFile , d , '\n' );
		} else
		if (objectType == "maxx" )
		{
			levelFile >> sizeX;
		} else
		if (objectType == "maxy" )
		{
			levelFile >> sizeY;
		} else
		if (objectType == "wall" )
		{
			levelFile >> type;
			levelFile >> mod;
			levelFile >> tex;
			w.push_back( new Wall ( mod , tex.c_str() , type , objectX , objectY ) );	
			percentage( (float)100/o_count );
		} else
		if (objectType == "exit" )
		{
			e = new Exit( objectX , objectY );
			percentage( (float)100/o_count );
		} else
		if (objectType == "player" )
		{
			p = new Player( objectX * 64 , objectY * 64 );
			p->setGridX( objectX );
			p->setGridY( objectY );
			percentage( (float)100/o_count );
		} else
		if (objectType == "key" )
		{
			k.push_back( new Key( objectX , objectY ) );
			percentage( (float)100/o_count );
		} else
		if (objectType == "door" )
		{
			door.push_back( new Door( objectX , objectY ) );
			percentage( (float)100/o_count );
		} else
			if (objectType == "breakable" )
		{
			breakable.push_back( new Breakable( objectX , objectY ) );
			percentage( (float)100/o_count );
		} else
		if (objectType == "jewel" )
		{
			levelFile >> o_In;
			i_var[0] = atoi ( o_In );
			levelFile >> mod;
			levelFile >> tex;
			j.push_back( new Jewel ( mod , tex , objectX , objectY , i_var[0] ) );
			percentage( (float)100/o_count );
		} else
		if (objectType == "beetle" )
		{
			levelFile >> o_In;
			i_var[0] = atoi ( o_In);
			levelFile >> o_In;
			i_var[1] = atoi ( o_In);
			b.push_back( new Beetle ( objectX , objectY , i_var[0] , i_var[1] ) );
			percentage( (float)100/o_count );
		} else
		if (objectType == "prop" )
		{
			levelFile >> o_In;		
			objectZ = atoi ( o_In );
			levelFile >> mod;
			levelFile >> tex;
			prop.push_back( new Prop ( mod , tex.c_str() , objectX - 32, objectY + 32 , objectZ ) );
			percentage( (float)100/o_count );
		}
		loadScreen( win );
	}
	cout << endl;
	levelFile.close();
	ready = 1;
	loadScreen( win );
	return true;
}

void WorldSpawn::draw( vector<Wall*>& w, vector<Jewel*>& j , vector<Beetle*>& b , vector<Key*>& k , vector<Door*>& door , vector<Breakable*>& breakable, Player*& p, Exit*& e, vector<Prop*>& o ) // Draws the current world
{	
	e->draw();
	for ( unsigned int i = 0; i < w.size(); ++i ){ w[i]->draw(); }
	for ( unsigned int i = 0; i < j.size(); ++i ){ j[i]->draw(); }
	for ( unsigned int i = 0; i < o.size(); ++i ){ o[i]->draw(); }
	for ( unsigned int i = 0; i < b.size(); ++i ){ b[i]->draw(); }
	for ( unsigned int i = 0; i < k.size(); ++i ){ k[i]->draw(); }
	for ( unsigned int i = 0; i < door.size(); ++i ){ door[i]->draw(); }
	for ( unsigned int i = 0; i < breakable.size(); ++i ){ breakable[i]->draw(); }
	p->draw();
}

bool WorldSpawn::clean( vector<Wall*>& w, vector<Jewel*>& j , vector<Beetle*>& b , vector<Key*>& k , vector<Door*>& door ,vector<Breakable*>& breakable ,  Player*& p, Exit*& e, vector<Prop*>& prop , string& s_loc , int& i_no )
{
   	delete p;	
	delete e;
	for ( unsigned int i = 0; i < w.size(); ++i ){ delete w[i]; }
	w.clear();
	for ( unsigned int i = 0; i < j.size(); ++i ){ delete j[i]; }
	j.clear();
	for ( unsigned int i = 0; i < prop.size(); ++i ){ delete prop[i]; }
	prop.clear();
	for ( unsigned int i = 0; i < b.size(); ++i ){ delete b[i]; }
	b.clear();
	for ( unsigned int i = 0; i < k.size(); ++i ){ delete k[i]; }
	k.clear();
	for ( unsigned int i = 0; i < door.size(); ++i ){ delete door[i]; }
	door.clear();
	for ( unsigned int i = 0; i < breakable.size(); ++i ){ delete breakable[i]; }
	breakable.clear();

	string s_dir = "resource/maps/level";
	string s_ext = ".lld";
	i_no = i_no + 1;
	oss << i_no;
	string s_id = oss.str();
	s_dir.append( s_id.append( s_ext ) );
	oss.str("");
	s_loc = s_dir;

	// Clean up own variables
	pcent = 0;
	ready = 0;
	o_count = 0;
	return true;
}
	
void WorldSpawn::loadScreen( sf::RenderWindow* win )
{
	l_bar.setSize(sf::Vector2f(  win->getSize().x/100 * pcent , (float)(win->getSize().y/32 ) ) );
	l_bar.setPosition( (float)win->getSize().x/32, (float)( win->getSize().y - win->getSize().y/8 ) );
	l_bar.setFillColor( sf::Color( 0 , 0 , 0 ) );
	win->pushGLStates();
	win->clear( sf::Color( 255 , 255 , 255 ) );
	win->draw( s_ctrl );
	win->draw( s_lvl );
	if( ready == 0 )
	{
		win->draw( l_bar );
	}
		win->popGLStates();
	while( ready == 1 )
	{
		win->pushGLStates();
		win->clear( sf::Color( 255 , 255 , 255 ) );
		win->draw( s_ctrl );
		win->draw( s_lvl );
		win->draw( s_ready );
		win->popGLStates();
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) ready = 0;
		win->display();
	}

	win->display();
}

void WorldSpawn::percentage( float d )
{
	pcent = pcent + d;
	if(pcent > 99)pcent = 100;
}


// Getters
int WorldSpawn::getSizeX(){ return sizeX; }
int WorldSpawn::getSizeY(){ return sizeY; }

WorldSpawn::~WorldSpawn(){

}