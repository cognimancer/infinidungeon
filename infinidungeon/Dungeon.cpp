#include <stdexcept>
#include "Dungeon.h"

Dungeon::Dungeon() : _rmID( 0 ), _map( map2d() ) {}

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

void Dungeon::renderRoom( int row, int col ) {
	map2d::const_iterator checkRow = _map.find( row );
	map2d::const_iterator checkRowNorth = _map.find( row - 1 );
	map2d::const_iterator checkRowSouth = _map.find( row + 1 );
	if( checkRow == _map.end() ) {
		_map[row] = std::unordered_map<int, Room*>();
	}
	if( checkRowNorth == _map.end() ) {
		_map[row - 1] = std::unordered_map<int, Room*>();
	}
	if( checkRowSouth == _map.end() ) {
		_map[row + 1] = std::unordered_map<int, Room*>();
	}
	// all three rows exist at this point
	if( _map[row].find( col ) == _map[row].end() ) {
		_map[row][col] = new Room( "room" + _rmID++, row, col );
	}
	if( _map[row - 1].find( col ) == _map[row - 1].end() ) {
		_map[row - 1][col] = new Room( "room" + _rmID++, row - 1, col, 180.0f ); //FIXME temp hard-coded rotation to demo two connected rooms
	}
	if( _map[row + 1].find( col ) == _map[row + 1].end() ) {
		_map[row + 1][col] = new Room( "room" + _rmID++, row + 1, col );
	}
	if( _map[row].find( col - 1 ) == _map[row].end() ) {
		_map[row][col - 1] = new Room( "room" + _rmID++, row, col - 1 );
	}
	if( _map[row].find( col + 1 ) == _map[row].end() ) {
		_map[row][col + 1] = new Room( "room" + _rmID++, row, col + 1 );
	}
	//TODO rooms need to have appropriate doorways
	//TODO rooms only need to be rendered if there's a doorway to them.
	// all five rooms exist at this point
	_map[row][col]->render();		// current room
	_map[row - 1][col]->render();	// north neighbor
	_map[row + 1][col]->render();	// south neighbor
	_map[row][col - 1]->render();	// west neighbor
	_map[row][col + 1]->render();	// east neighbor
}