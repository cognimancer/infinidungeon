#ifndef ROOM_H
#define ROOM_H
#include <string>
#include "ModelManagerClass.h"
class Room; //avoid circular dependency
#include "Dungeon.h"

class Room {
public:
	static const int ROOM_DEADEND = 1; // exits: north
	static const int ROOM_ELBOW = 2; //exits: north, west
	static const int ROOM_HALL = 3; //exits: north, south
	static const int ROOM_T_JOINT = 4; //exits: north, west, south
	static const int ROOM_CROSSROADS = 5; //exits: north, south, east, west
	
	static float roomWidth() { return 57.4f; }
	Room *north;
	Room *east;
	Room *south;
	Room *west;
	bool exitNorth;
	bool exitEast;
	bool exitSouth;
	bool exitWest;

	//room rotations are clockwise
	Room( Dungeon* theDungeon, std::string name, int row = 0, int col = 0, int roomType = 1, int rotation = 0 );
	void render(bool renderNeighbors = false);

	int getColumn();
	int getRow();

private:
	std::string _name;
	int _rotation;
	int _row;
	int _col;
	Dungeon* dungeonInstance;

	void setModelMatrix();
};

#endif