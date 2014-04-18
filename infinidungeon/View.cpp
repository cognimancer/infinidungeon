#include "View.h"
#include "TitleScreen.h"
#include "DungeonScreen.h"

AbstractScreen *View::currentInstance;

View::View() {}
View::View( const View &other ) {}
View &View::operator=( const View &other ) { return *this; }
View::~View() {
	if( currentInstance ) delete currentInstance;
}

void View::changeScreen( ViewID screen ) {
	if( currentInstance ) delete currentInstance;
	switch( screen ) {
	case Title:
		currentInstance = new TitleScreen( this );
		break;
	case Dungeon:
		currentInstance = new DungeonScreen( this );
		break;
	}
}

void View::display() {
	currentInstance->display();
}

void View::idle() {
	currentInstance->idle();
}

void View::keyboard( unsigned char key, int x, int y ) {
	currentInstance->keyboard( key, x, y );
}

void View::keyboardUp( unsigned char key, int x, int y ) {
	currentInstance->keyboardUp( key, x, y );
}

void View::special( int key, int x, int y ) {
	currentInstance->special( key, x, y );
}

void View::specialUp( int key, int x, int y ) {
	currentInstance->specialUp( key, x, y );
}