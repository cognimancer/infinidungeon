#include "Room.h"

Room::Room( std::string name ) : _name( name ), _rotation( 0.0f ), _x( 0 ), _y( 0 ),
		north( nullptr ), east( nullptr ), south( nullptr ), west( nullptr ) {
	ModelManagerClass::GetInstance()->LoadModel( "Room1.obj", name );
}

void Room::render() {
	ModelManagerClass::GetInstance()->RenderModel( _name );
}

void Room::setRotation( float deg ) {
	_rotation = deg;
	setModelMatrix();
}

void Room::setPosition( int x, int y ) {
	_x = x;
	_y = y;
	setModelMatrix();
}

void Room::setModelMatrix() {
	glm::mat4 matrix = glm::translate( glm::mat4(), glm::vec3( roomWidth()*_x, 0.0f, roomWidth()*_y ) );
	matrix = glm::rotate(matrix, _rotation, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	ModelManagerClass::GetInstance()->SetModelMatrix( matrix, _name );
}