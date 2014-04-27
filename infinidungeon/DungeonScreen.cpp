#include "DungeonScreen.h"

DungeonScreen::DungeonScreen( View *view ) : AbstractScreen( view ),
		initialTime( (float)glutGet( GLUT_ELAPSED_TIME ) ),
		_moveForward( false ),
		_moveBackward( false ),
		_moveRight( false ),
		_moveLeft( false ),
		_rotateRight( false ),
		_rotateLeft( false ),
		_shape( new Cube() ) {
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
	delete _shape;
}

void DungeonScreen::display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window
	glEnable( GL_DEPTH_TEST );
	_shape->render();
	glutSwapBuffers();
} // display

void DungeonScreen::idle() {
	finalTime = (float)glutGet( GLUT_ELAPSED_TIME );
	float dt = (finalTime - initialTime)/500;
	if( _moveForward ) {
		std::cout << "moving forward" << std::endl;
		Camera::getInstance()->moveForward( 1.1f );
	}
	if( _moveBackward ) {
		std::cout << "moving backward" << std::endl;
		Camera::getInstance()->moveForward( -1.1f );
	}
	if( _moveRight ) {
		std::cout << "moving right" << std::endl;
		Camera::getInstance()->moveSideways( 1.1f );
	}
	if( _moveLeft ) {
		std::cout << "moving left" << std::endl;
		Camera::getInstance()->moveSideways( -1.1f );
	}
	if( _rotateRight ) {
		std::cout << "rotating right" << std::endl;
		Camera::getInstance()->rotate( 1.1f );
	}
	if( _rotateLeft ) {
		std::cout << "rotating left" << std::endl;
		Camera::getInstance()->rotate( -1.1f );
	}
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
	switch( key ) {
	case GLUT_KEY_UP:
		_moveForward = true;
		break;
	case GLUT_KEY_DOWN:
		_moveBackward = true;
		break;
	case GLUT_KEY_RIGHT:
		_moveRight = true;
		break;
	case GLUT_KEY_LEFT:
		_moveLeft = true;
		break;
	case GLUT_KEY_HOME:
		_rotateLeft = true;
		break;
	case GLUT_KEY_END:
		_rotateRight = true;
		break;
	}
} // special

void DungeonScreen::specialUp( int key, int x, int y ) {
	switch( key ) {
	case GLUT_KEY_UP:
		_moveForward = false;
		break;
	case GLUT_KEY_DOWN:
		_moveBackward = false;
		break;
	case GLUT_KEY_RIGHT:
		_moveRight = false;
		break;
	case GLUT_KEY_LEFT:
		_moveLeft = false;
		break;
	case GLUT_KEY_HOME:
		_rotateLeft = false;
		break;
	case GLUT_KEY_END:
		_rotateRight = false;
		break;
	}
} // specialUp