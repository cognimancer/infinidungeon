#include "Room.h"

Room::Room( std::string name, int row, int col, float rotation ) : _name( name ), _rotation( rotation ), _row( row ), _col( col ),
		north( nullptr ), east( nullptr ), south( nullptr ), west( nullptr ) {
	ModelManagerClass::GetInstance()->LoadModel( "Room2.obj", name );
	setModelMatrix();
}

void Room::render() {
	ModelManagerClass::GetInstance()->RenderModel( _name );
}

void Room::setRotation( float deg ) {
	_rotation = deg;
	setModelMatrix();
}

void Room::setPosition( int row, int col ) {
	_row = row;
	_col = col;
	setModelMatrix();
}

void Room::setModelMatrix() {
	glm::mat4 matrix = glm::translate( glm::mat4(), glm::vec3( roomWidth()*_col, 0.0f, roomWidth()*_row ) );
	matrix = glm::rotate(matrix, _rotation, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	ModelManagerClass::GetInstance()->SetModelMatrix( matrix, _name );
}