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
		_lookUpDown( 0.0f ),
		_lookLeftRight( 0.0f ),
		_sprinting( false )
		{
			_modelMan = ModelManagerClass::GetInstance();
			//_modelMan->LoadModel("Room1.obj", "Room1");
			//_modelMan->LoadModel("Room1.obj", "Room2");
			_currentRoom = new Room( "room1" );
			_currentRoom->north = new Room( "room2" );
			_currentRoom->north->setPosition( 0, -1 );
			_currentRoom->north->setRotation( 180.0f );
			std::cout << "Models: " << _modelMan->GetNumberOfModels() << std::endl;
			std::cout << "Instances: " << _modelMan->GetNumberOfInstances() << std::endl;
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
	delete _modelMan;
	delete _currentRoom->north;
	delete _currentRoom;
}

void DungeonScreen::display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     // clear the window
	glEnable( GL_DEPTH_TEST );
	glm::mat4 matrix = glm::translate( glm::mat4(), glm::vec3( 0.0f, 0.0f, -57.0f ) );
	matrix = glm::rotate(matrix, 180.0f, glm::vec3( 0.0f, 1.0f, 0.0f ) );
//	_modelMan->SetModelMatrix(glm::mat4(), "Room1");
//	_modelMan->SetModelMatrix(matrix, "Room2");
	_currentRoom->render();
	_currentRoom->north->render();
//	_modelMan->RenderModel();
	glutSwapBuffers();
} // display

void DungeonScreen::idle() {
	finalTime = (float)glutGet( GLUT_ELAPSED_TIME );
	float dt = (finalTime - initialTime)/500;

	//std::cout << "Models: " << _modelMan->GetNumberOfModels() << std::endl;
	//std::cout << "Instances: " << _modelMan->GetNumberOfInstances() << std::endl;

	Camera::getInstance()->setSpeed( _sprinting ? 9.0f : 3.0f );
	glm::vec2 rotation = glm::vec2(0.0f);
	glm::vec3 directions = glm::vec3(0.0f);

	if(_moveRight) directions.y -= 1.0f;
	if(_moveLeft) directions.y += 1.0f;
	if(_moveForward) directions.x += 1.0f;
	if(_moveBackward) directions.x -= 1.0f;
	if(_rotateRight) rotation.x += 0.02f;
	if(_rotateLeft) rotation.x -= 0.02f;
	if(_rotateUp) rotation.y -= 0.02f;
	if(_rotateDown) rotation.y += 0.02f;
	if(_lookLeftRight != 0.0f) rotation.x += _lookLeftRight;
	if(_lookUpDown != 0.0f) rotation.y += _lookUpDown;
	if(_lookLeftRight || _lookUpDown ) 
		glutWarpPointer( 320, 240 );

	Camera::getInstance()->move(directions, rotation, dt);

	glutPostRedisplay();
	initialTime = finalTime;
} // idle

void DungeonScreen::keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case 27: // esc
		glutLeaveMainLoop();
		break;
	case 'a':
	case 'A':
		_moveLeft = true;
		break;
	case 'd':
	case 'D':
		_moveRight = true;
		break;
	case 'w':
	case 'W':
		_moveForward = true;
		break;
	case 's':
	case 'S':
		_moveBackward = true;
		break;
	case 15: // shift
		_sprinting = true;
		break;
	}
} // keyboard

void DungeonScreen::keyboardUp( unsigned char key, int x, int y ) {
	switch( key ) {
	case 'a':
	case 'A':
		_moveLeft = false;
		break;
	case 'd':
	case 'D':
		_moveRight = false;
		break;
	case 'w':
	case 'W':
		_moveForward = false;
		break;
	case 's':
	case 'S':
		_moveBackward = false;
		break;
	case 15: //shift
		_sprinting = false;
		break;
	}
} // keyboardUp

void DungeonScreen::special( int key, int x, int y ) {
	switch( key ) {
	case GLUT_KEY_UP:
		_rotateUp = true;
		break;
	case GLUT_KEY_DOWN:
		_rotateDown = true;
		break;
	case GLUT_KEY_RIGHT:
		_rotateRight = true;
		break;
	case GLUT_KEY_LEFT:
		_rotateLeft = true;
		break;
	case GLUT_KEY_SHIFT_L:
		_sprinting = true;
		break;
	}
} // special

void DungeonScreen::specialUp( int key, int x, int y ) {
	switch( key ) {
	case GLUT_KEY_UP:
		_rotateUp = false;
		break;
	case GLUT_KEY_DOWN:
		_rotateDown = false;
		break;
	case GLUT_KEY_RIGHT:
		_rotateRight = false;
		break;
	case GLUT_KEY_LEFT:
		_rotateLeft = false;
		break;
	case GLUT_KEY_SHIFT_L:
		_sprinting = false;
		break;
	}
} // specialUp

void DungeonScreen::mouseMotion( int x, int y ) {
} //mouseMotion

void DungeonScreen::mousePassive( int x, int y ) {
	_lookLeftRight = 0.002f * (x - 320);
	_lookUpDown = 0.002f * (y - 240);
} // mousePassive