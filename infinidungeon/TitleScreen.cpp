#include "TitleScreen.h"

TitleScreen::TitleScreen( View *view ) : AbstractScreen( view ) {}
TitleScreen::TitleScreen( const TitleScreen &other ) : AbstractScreen( other._view ) {}
TitleScreen &TitleScreen::operator=( const TitleScreen &other ) {
	if( this != &other ) {
		_view = other._view;
		_shader = other._shader;
		glutPostRedisplay();
	}
	return *this;
}
TitleScreen::~TitleScreen() {}

void TitleScreen::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );
	printText( -70, 80, "infinidungeon" );
	printText( -100, 40, "the infinite dungeon" );
	printText( -100, -100, "press space to start" );
	glutSwapBuffers();
}

void TitleScreen::keyboard( unsigned char key, int x, int y ) {
	switch ( key ) {
	case ' ':
		std::cout << "going to dungeon screen" << std::endl;
		_view->changeScreen( View::Dungeon );
		break;
	case 27: // esc
		glutLeaveMainLoop();
		break;
	}
}