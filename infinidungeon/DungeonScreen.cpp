#include "DungeonScreen.h"

DungeonScreen::DungeonScreen( View *view ) : AbstractScreen( view ),
		initialTime( (float)glutGet( GLUT_ELAPSED_TIME ) ) {
}

DungeonScreen::DungeonScreen( const DungeonScreen &other ) : AbstractScreen( other._view ),
	initialTime( (float)glutGet( GLUT_ELAPSED_TIME ) ) {
}

DungeonScreen &DungeonScreen::operator=( const DungeonScreen &other ) {
	if( this != &other ) {
		_view = other._view;
		_shader = other._shader;
		glutPostRedisplay();
		initialTime = (float)glutGet( GLUT_ELAPSED_TIME );
	}
	return *this;
}

DungeonScreen::~DungeonScreen() {
}

void DungeonScreen::display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window
	glEnable( GL_DEPTH_TEST );
	for( int i = -320; i < 320; i += 190 )
		for( int j = -240; j < 240; j += 15 )
			printText( i, j, "you are exploring..." );
	glutSwapBuffers();
} // display

void DungeonScreen::idle() {
	finalTime = (float)glutGet( GLUT_ELAPSED_TIME );
	float dt = (finalTime - initialTime)/500;
	glutPostRedisplay();
	initialTime = finalTime;
} // idle

void DungeonScreen::keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27: // esc
		glutLeaveMainLoop();
		break;
	}
} // keyboard

void DungeonScreen::keyboardUp( unsigned char key, int x, int y ) {
} // keyboardUp

void DungeonScreen::special( int key, int x, int y ) {
} // special

void DungeonScreen::specialUp( int key, int x, int y ) {
} // specialUp