#include <stdexcept>
#include "Dungeon.h"

Dungeon::Dungeon() : _roomCount( 0 ), _map( map2d() ) {}

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
	//TODO: not always crossroads
	if (_map[row].find(col) == _map[row].end()) _map[row][col] = new Room( this, "room" + std::to_string(_roomCount++), row, col, Room::ROOM_CROSSROADS);

	return _map[row][col];
}