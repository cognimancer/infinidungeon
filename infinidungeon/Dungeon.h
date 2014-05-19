#ifndef DUNGEON_H
#define DUNGEON_H
#include <unordered_map>
#include "Room.h"
typedef std::unordered_map<int, std::unordered_map<int, Room*>> map2d;

class Dungeon {
public:
	Dungeon();
	~Dungeon();

	void renderRoom( int row, int col );
private:
	// row-major map of rooms
	map2d _map;
	int _rmID;
};

#endif