#include "DungeonScreen.h"

DungeonScreen::DungeonScreen( View *view ) : AbstractScreen( view ),
		initialTime( (float)glutGet( GLUT_ELAPSED_TIME ) ),
		_moveForward( false ),
		_moveBackward( false ),
		_moveRight( false ),
		_moveLeft( false ),
		_rotateRight( false ),
		_rotateLeft( false ),
		_rotateUp( false ),
		_rotateDown( false ),
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

	glm::vec2 rotation;
	glm::vec3 directions;

	if(_moveRight) directions.y = -1;
	if(_moveLeft) directions.y = 1;
	if(_moveForward) directions.x = 1;
	if(_moveBackward) directions.x = -1;
	if(_rotateRight) rotation.x = 0.02f;
	if(_rotateLeft) rotation.x = -0.02f;
	if(_rotateUp) rotation.y = -0.02f;
	if(_rotateDown) rotation.y = 0.02f;

	Camera::getInstance()->move(directions, rotation, 1.0f);

	glutPostRedisplay();
	initialTime = finalTime;
} // idle

void DungeonScreen::keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27: // esc
		glutLeaveMainLoop();
		break;
	case 'a':
		_rotateLeft = true;
		break;
	case 'd':
		_rotateRight = true;
		break;
	case 'w':
		_rotateUp = true;
		break;
	case 's':
		_rotateDown = true;
		break;
	}
} // keyboard

void DungeonScreen::keyboardUp( unsigned char key, int x, int y ) {
	switch( key ) {
	case 'a':
		_rotateLeft = false;
		break;
	case 'd':
		_rotateRight = false;
		break;
	case 'w':
		_rotateUp = false;
		break;
	case 's':
		_rotateDown = false;
		break;
	}
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
	}
} // specialUp