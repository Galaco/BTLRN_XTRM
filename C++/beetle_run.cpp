#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "game.h"
#include "settings.h"

using namespace std;


int main()
{
	// Prepare and load game cfg before doing anything else
	Settings settings;
	settings.read();								// Loads cfg
	unsigned int width = settings.getWidth();		// Prepare window width
	unsigned int height = settings.getHeight();	// Prepare window height
	sf::ContextSettings cs;
	cs.majorVersion = 3;
	cs.minorVersion = 2;
	cs.depthBits = 24;
	cs.stencilBits = 8;
	cs.antialiasingLevel = settings.getAA();

	// Create Window
    sf::RenderWindow App( sf::VideoMode( width , height ), "BTLRN XTRM - v1.2a" , sf::Style::Close, cs );  
	Game g( &App );
	App.setVerticalSyncEnabled( settings.getVsync() );

	// OpenGL setup	
    glClearDepth( 1.f );							// Set color and depth clear value
    glClearColor( 0.f , 0.f , 0.f , 0.f );
    glEnable( GL_DEPTH_TEST );						// Enable Z-buffer read and write
	glDepthFunc( GL_LEQUAL );
    glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable( GL_LIGHTING );						// Enable Lighting 
    glMatrixMode( GL_PROJECTION );					// Setup a perspective projection
	glDisable(GL_COLOR_MATERIAL);
    glLoadIdentity();
    gluPerspective( 90.f , width/height , 1.f , 1536.f );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	g.init();					// Initialise game - loads resources

	// Start the game loop
    while ( App.isOpen() )
    {	
		App.setActive();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		g.play(); 											
    }
    return EXIT_SUCCESS;
}