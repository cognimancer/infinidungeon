#ifndef ROOM_H
#define ROOM_H
#include <string>
#include "ModelManagerClass.h"

class Room {
public:
	static float roomWidth() { return 58.0f; }
	Room *north;
	Room *east;
	Room *south;
	Room *west;

	Room( std::string name, int row = 0, int col = 0, float rotation = 0.0f );
	void render();
	void setRotation( float deg = 0.0f );
	void setPosition( int row = 0, int col = 0 );

private:
	std::string _name;
	float _rotation;
	int _row;
	int _col;

	void setModelMatrix();
};

#endif