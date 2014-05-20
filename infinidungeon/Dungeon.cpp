#include <stdexcept>
#include <time.h>
#include "Dungeon.h"

Dungeon::Dungeon() : _roomCount( 0 ), _map( map2d() ) {
	srand( time( NULL ) );
}

Dungeon::~Dungeon() {
	for( map2d::iterator row = _map.begin(); row != _map.end(); row++ ) {
		for( std::unordered_map<int, Room*>::iterator room = row->second.begin();
				room != row->second.end(); room++ ) {
			delete room->second;
		}
		row->second.clear();
	}
	_map.clear();
}

Room* Dungeon::getRoom(int row, int col) {
	if (_map.find(row) == _map.end()) _map[row] = std::unordered_map<int, Room*>(); //create row if it doesn't exist

	//if there is no room at given coords, create one
	if (_map[row].find(col) == _map[row].end()) {

		// decide which exits to open
		// keeping track of doors ensures no boxed-in rooms. (if 3 walls are doorless, fourth wall has 100% chance to have door)
		// this way won't be symmetrical, but it's what I came up with on short notice.
		int numDoors = 0;
		bool east = (_map[row].find(col+1) == _map[row].end()) ?
			(rand() % (4-numDoors) == 1) : _map[row][col+1]->exitWest;
		if( east ) ++numDoors;
		bool west = (_map[row].find(col-1) == _map[row].end()) ?
			(rand() % (4-numDoors) == 1) : _map[row][col-1]->exitEast;
		if( west ) ++numDoors;
		bool north = (_map.find(row+1) == _map.end() || _map[row+1].find(col) == _map[row+1].end()) ?
			(rand() % (4-numDoors) == 1) : _map[row+1][col]->exitSouth;
		if( north ) ++numDoors;
		bool south = (_map.find(row-1) == _map.end() || _map[row-1].find(col) == _map[row-1].end()) ?
			(rand() % (4-numDoors) == 1) : _map[row-1][col]->exitNorth;
		if( south ) ++numDoors;

		//determine room type and rotation
		int type = 0;
		int rotation = 0;
		if( numDoors == 4 )
			type = Room::ROOM_CROSSROADS;
		else if( numDoors == 3 ) {
			type = Room::ROOM_T_JOINT;
			rotation = !east ? 0 : !west ? 180 : !north ? 270 : 90;
		} else if( numDoors == 1 ) {
			type = Room::ROOM_DEADEND;
			rotation = east ? 270 : west ? 90 : north ? 180 : 0;
		} else if( east && west && !north && !south ) {
			type = Room::ROOM_HALL;
			rotation = 90;
		} else if( !east && !west && north && south ) {
			type = Room::ROOM_HALL;
		} else {
			type = Room::ROOM_ELBOW;
			if( east ) rotation = north ? 180 : 270;
			if( west ) rotation = south ? 0 : 90;
		}

		_map[row][col] = new Room( this, "room" + std::to_string(_roomCount++), row, col, type, rotation );
	}
	return _map[row][col];
}