#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "AbstractScreen.h"

// The first screen displayed
class TitleScreen : public AbstractScreen {
public:
	TitleScreen( View *view );
	TitleScreen( const TitleScreen &other );
	TitleScreen &operator=( const TitleScreen &other );
	~TitleScreen();
	
	// glut I/O functions
	void display();
	void idle() {}
	void keyboard( unsigned char key, int x, int y );
	void keyboardUp( unsigned char key, int x, int y ) {}
	void special( int key, int x, int y ) {}
	void specialUp( int key, int x, int y ) {}
	void mouseMotion( int x, int y ) {}
	void mousePassive( int x, int y ) {}
};

#endif