#include "game.h"

Game::Game( sf::RenderWindow* app ) : win( app ) //initialise window
{
	//set the dimensions for window
	width = app->getSize().x;
	height = app->getSize().y;		
	canPress = true;
	levelLocation = "resource/maps/level1.lld";								// Set initial level location
	// Set system Stuff
	cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<endl;				// Display openGL version
	win->setFramerateLimit( FRAMERATE );									// Set framerate
	cout << "Framerate set to: " << FRAMERATE << "fps" << endl;				// Display framerate
}

Game::Game() //constructor
{
}

void Game::init()
{
	if( state == "mainmenu" )
	{
		level = 1;
		levelLocation = "resource/maps/level1.lld";	
	}

	if( state == "play" )
	{
		win->pushGLStates();
		if( !world.build( wall , jewel , beetle , key , door , breakable , player , exit , prop , win , levelLocation ) )
			hud.setState( "inputname" ); 
		win->popGLStates();
		lvlX = world.getSizeX();
		lvlY = world.getSizeY();
	}	
	hud.startup( win );
}

void Game::draw()
{
	if( state == "mainmenu" )
	{
		win->pushGLStates();
		win->clear( sf::Color( 150 , 150 , 255 ) );
		hud.draw( win );
		win->popGLStates();
	} else
	if( state == "scores" )
	{
		win->pushGLStates();
		win->clear( sf::Color( 150 , 150 , 255 ) );
		hud.draw( win );
		win->popGLStates();
	} else
	if( state == "inputname" )
	{
		win->pushGLStates();
		win->clear( sf::Color( 150 , 150 , 255 ) );
		hud.draw( win );
		win->popGLStates();
	} else
	if( state == "play" )
	{
		win->clear( sf::Color( 150 , 150 , 255 ) );
		world.draw( wall , jewel , beetle , key , door , breakable , player , exit , prop );
		win->pushGLStates();
		hud.draw( win );
		win->popGLStates();
	} else
	if( ( state == "pause" ) || ( state == "pickup" ) )
	{
		world.draw( wall , jewel , beetle , key , door , breakable , player , exit , prop );
		win->pushGLStates();
		hud.draw( win );
		win->popGLStates();
	}
}

void Game::getInput()
{
	sf::Event Event;
    while ( win->pollEvent( Event ) ) 
	{
		if( ( sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Up ) || ( sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Down ) ) canPress = true;
		if( Event.type == sf::Event::Closed ) win->close();

		if( state == "inputname" )
		{

			if( sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Back )
				hud.removeChar();
			else
			if( Event.type == sf::Event::TextEntered )
				if (Event.text.unicode < 128){
					hud.addChar(  static_cast<char>(Event.text.unicode) );
				}
		}
	
		if( sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape )
			if( state == "play" )
				hud.setState( "mainmenu" );
			else
				win->close(); // Escape key : exit	
	}	

	if( state == "mainmenu" )
	{
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && canPress == true ){ hud.setSelPos( 0 ); canPress = false; }
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && canPress == true ){ hud.setSelPos( 1 ); canPress = false; }
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )	hud.setPressed( 1 );
	}

	if( state == "play" )
	{
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::M ) ) camera.zoom( 4 );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::N ) ) camera.zoom( -4 );		
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && hud.hasPound() == true ) player->pound();	
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){ player->move( 'r' ); player->setDir( 1 ); }
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){ player->move( 'l' ); player->setDir ( 0 ); }
		if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) && hud.getHealth() > 4 ) player->jump( 30 );
		if ( !( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) && !( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) && !( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) && !( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) && (player->getVelY()<4) ) player->setState( "IDLE" );
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::P ) ){ state = "pause"; hud.setState( "pause" ); }
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) player->setState( "RUN" );
	}

	if( state == "pause" ) if ( sf::Keyboard::isKeyPressed( sf::Keyboard::R ) ){ hud.setState( "play" ); }
	if( state == "pickup" ) if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){ hud.setState( "play" ); }

	if( state == "inputname" )
	{
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) 
			hud.setState( "calculate" );
	}

	if( state == "scores" ) if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Back ) ) hud.setState( "mainmenu" );
}
	

void Game::update()
{		


	t_Clock = Clock.getElapsedTime();
	if( t_Clock.asMilliseconds()/10 > 1.0F / FRAMERATE )
	{	
		if( state == "mainmenu" ) 
		{
			hud.update();
			if ( hud.getState() == "close" ) win->close();
		}
		if( ( state== "pause" ) || ( state== "pickup" ) || ( state== "calculate" ) || ( state== "inputname" ) )
		{
			hud.update();
		}

		if( state == "play" )
		{
			//*****************************************************************************
			// Physics calculations etc
			//*****************************************************************************
			//player velocities
			player->setVelY( physics.gravity( player->getVelY() ) );
			player->setVelX( physics.friction( player->getVelX() ) );


			
			//*****************************************************************************
			// Update UI + System Objects
			//*****************************************************************************
			hud.update();
			camera.update( player->getPosX() , player->getPosY() );


			//*****************************************************************************
			// Update World Objects
			//*****************************************************************************
			player->update();
			for (unsigned int i=0; i<door.size(); ++i){ door[i]->update(); }
			for (unsigned int i=0; i<jewel.size(); ++i){ jewel[i]->update(); }
			for (unsigned int i=0; i<beetle.size(); ++i){ beetle[i]->update(); beetle[i]->checkPlayerVis( player->getPosX() , player->getPosY() ); }
			exit->update();


			//*****************************************************************************
			// Collision checks with Objects
			//*****************************************************************************
			// COLLISIONS INVOLVING PLAYER AS PRIORITY (Object 1 )
			//wall
			for ( unsigned int i = 0; i < wall.size(); ++i ) {
				if( wall[i]->getType() == 'n' ) {
					if( physics.checkGrid( player , wall[i] ) ) {
						switch (physics.checkAABB( player , wall[i] ) ) {
						case 'l': {
								player->setPosX( player->getPosX() - 3 );	
								player->setVelX( 0 );
								break;
							 }
						case 'r': {
								player->setPosX( player->getPosX() + 3 );	
								player->setVelX( 0 );	
								break;
							}
							case 'd': {	
								player->setVelY( -1 );
								break;
								}
							case 'u': {	
								if(player->getVelY() <= -12 ){
									player->setVelY(12);
								} else {
									player->setPosY( wall[i]->getPosY()+wall[i]->getSizeY()+wall[i]->getVelY() );
									player->setVelY( 0 );	
								} break;
			}	}	}	}  else
				if( wall[i]->getType() == 'p' ) {
						if( physics.checkGrid( player , wall[i] ) ) {
							switch (physics.checkAABB( player , wall[i] ) ) {
								case 'u': {	
									if(player->getVelY() <= -12 ){
									player->setVelY(12);
								} else {
									/*if(player->getPosY()  wall[i]->getPosY()+wall[i]->getSizeY() ){
										player->setPosY( player->getPosY() + 2 );
										player->setVelY( 0 );
									}
									else*/
										player->setPosY( wall[i]->getPosY()+wall[i]->getSizeY()+wall[i]->getVelY() );
										player->setVelY( 0 );	
									}	
									break;
				}	}	}	}
			}	
			//jewel
			for ( unsigned int i = 0; i < jewel.size(); ++i ) {
				if( physics.checkGrid( player , jewel[i] ) ) {
					switch (physics.checkAABB( player , jewel[i] ) ) {
						case 'l': case 'r': case 'd': case 'u':				
						{		
							if(jewel[i]->getSpecial())
							{	
								hud.setState( "pickup");
								hud.grantPound();
							}  else
							player->playSound( "collect" );

							delete jewel[i];
							jewel.erase( jewel.begin() + i );
							hud.addScore( 10 , 1 );
							break;
			}	}	}	}		
			//key
			for ( unsigned int i = 0; i < key.size(); ++i ) {
				if( physics.checkGrid( player , key[i] ) ) {
					switch (physics.checkAABB( player ,key[i] ) ) {
						case 'l': case 'r': case 'd': case 'u':				
						{		
							delete key[i];
							key.erase( key.begin() + i );
							hud.addKeys( 1 );
							break;
			}	}	}	}	
			//door
			for ( unsigned int i = 0; i < door.size(); ++i ) {
				if( physics.checkGrid( player , door[i] ) ) {
					switch (physics.checkAABB( player ,door[i] ) ) {
						case 'l': case 'r': case 'd': case 'u':				
						{		
							if(door[i]->open(hud.hasKey()))
								hud.addKeys(-1);
							else {
								player->setPosX( player->getPosX() -3 );
								player->setVelX( 0 );
							}
							break;
			}	}	}	}
			//breakables
			for ( unsigned int i = 0; i < breakable.size(); ++i ) {
				if( physics.checkGrid( player , breakable[i] ) ) {
					switch (physics.checkAABB( player ,breakable[i] ) ) {
						case 'l': case 'r': case 'd': case 'u':				
						{		
							if(player->getVelY() <= -12 ){
								delete breakable[i];
								breakable.erase( breakable.begin() + i );
								player->setPosY( player->getPosY() +1 );
								player->setVelY(12);
							} else {
								player->setPosY( player->getPosY() +1 );
								player->setVelY(0);
							} break;
			}	}	}	}
			//exit
			if( physics.checkGrid( player , exit ) ) {
				switch (physics.checkAABB( player , exit ) ) {
					case 'l': case 'r':	case 'd': case 'u':																						
					{		
						world.clean( wall , jewel , beetle , key , door , breakable , player , exit , prop , levelLocation , level );
						init();
						break;
			}	}	}
			//beetle
			for ( unsigned int i = 0; i < beetle.size(); ++i ) {
				if( physics.checkGrid( player , beetle[i] ) ) {
					switch (physics.checkAABB( player , beetle[i] ) ) {
						case 'l': case 'r': case 'd': case 'u':				
						{		
							player->playSound( "death" );
							hud.addHealth( 10, false );
							hud.addLives( -1 , true );
							--level;
							world.clean( wall , jewel , beetle , key , door , breakable , player , exit , prop , levelLocation , level );
							init();
							break;
			}	}	}	}

			// COLLISIONS INVOLVING BEETLE AS PRIORITY (Object 1 )
			//jewel
			for ( unsigned int i = 0; i < beetle.size(); ++i ) {
				for ( unsigned int j = 0; j < jewel.size(); ++j ) {
					if( physics.checkGrid( beetle[i] , jewel[j] ) && jewel[j]->getSpecial() ) {
						switch (physics.checkAABB( beetle[i] , jewel[j] ) ) {
							case 'l': case 'r': case 'u': case 'd':																													
							{																									
								beetle[i]->reverseDir();	
								break;
							}	
			}	}	}	}



			//checks edges of world collision
			if (player->getPosY() < 32 ){
				player->setPosY( 32 );
				player->setVelY( 0 );
			}
			if (player->getPosX() < 0 ) player->setPosX( 0 );
			if (player->getPosX()+player->getSizeX() > lvlX) player->setPosX( (float)lvlX - player->getSizeX() );


			//*****************************************************************************
			// Additional Win Checks
			//*****************************************************************************
			if( hud.getHealth() <= -2 )
			{
				hud.addLives( -1 , true );
				hud.addHealth( 10 , false );
				if( hud.getLives() <= 0 ){ 
					//state = "scores"; 
					hud.setState( "inputname" ); 
					world.clean( wall , jewel , beetle , key , door , breakable , player , exit , prop , levelLocation , level );
				} else {
					--level;
					world.clean( wall , jewel , beetle , key , door , breakable , player , exit , prop , levelLocation , level );
				}
				init();
			}
		}

		//*****************************************************************************
		// Uncategorisable
		//*****************************************************************************
		Clock.restart();
	} 


	if( state != hud.getState() ) {
		if( state == "pause" || state == "inputname" || ( state == "pickup" ) )
			state = hud.getState();
		else {
			state = hud.getState();
			init();
		}
	}
}


void Game::play()
{
	//the game loop
	draw();								//the offscreen buffer
	getInput();							//from the user to check for exit
	update();							//integrate user input and any game movement
	win->display();						//display the rendered frame
}

Game::~Game()
{
}