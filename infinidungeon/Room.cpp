#include "Room.h"
#include "Dungeon.h"

Room::Room( Dungeon* theDungeon, std::string name, int row, int col, int roomType, int rotation ) : dungeonInstance(theDungeon), _name( name ), _rotation( rotation ), _row( row ), _col( col ),
		north( nullptr ), east( nullptr ), south( nullptr ), west( nullptr ),
		exitNorth(false), exitEast(false), exitSouth(false), exitWest(false){
	//load model for given roomtype
	std::string modelString = "Room" + std::to_string(roomType) + ".obj";
	ModelManagerClass::GetInstance()->LoadModel( modelString, name );
	
	//set initial available exits for this roomtype
	//these are temporary; true exits will be modified by rotation
	bool n = false;
	bool s = false;
	bool e = false;
	bool w = false;
	switch(roomType) {
	case ROOM_DEADEND: n = true; break;
	case ROOM_ELBOW: n = true; w = true; break;
	case ROOM_HALL: n = true; s = true; break;
	case ROOM_T_JOINT: n = true; w = true; s = true; break;
	case ROOM_CROSSROADS: n = true; w = true; s = true; e = true; break;
	default:
		std::cout << "Error: illegal room type " << roomType << " in " << name << std::endl;
		system("pause");
		exit(0);
	}
	//modify available exits due to room rotation
	switch(rotation) {
	case 0: 
		exitNorth = n;
		exitEast = e;
		exitSouth = s;
		exitWest = w;
		break;
	case 90: 
		exitNorth = w;
		exitEast = n;
		exitSouth = e;
		exitWest = s;
		break;
	case 180: 
		exitNorth = s;
		exitEast = w;
		exitSouth = n;
		exitWest = e;
		break;
	case 270:
		exitNorth = e;
		exitEast = s;
		exitSouth = w;
		exitWest = n;
		break;
	default:
		std::cout << "Error: illegal rotation value " << rotation << " in " << name << std::endl;
		system("pause");
		exit(0);
	}

	setModelMatrix();
}

void Room::render(bool renderNeighbors) {
	ModelManagerClass::GetInstance()->RenderModel( _name );
	if (renderNeighbors) {
		if (exitNorth) {
			Room* northNeighbor = dungeonInstance->getRoom(_row-1, _col);
			north = northNeighbor;
			northNeighbor->south = this;
			northNeighbor->render(false);
		}
		if (exitSouth) {
			Room* southNeighbor = dungeonInstance->getRoom(_row+1, _col);
			south = southNeighbor;
			southNeighbor->north = this;
			southNeighbor->render(false);
		}
		if (exitEast) {
			Room* eastNeighbor = dungeonInstance->getRoom(_row, _col-1);
			east = eastNeighbor;
			eastNeighbor->west = this;
			eastNeighbor->render(false);
		}
		if (exitWest) {
			Room* westNeighbor = dungeonInstance->getRoom(_row, _col+1);
			west = westNeighbor;
			westNeighbor->east = this;
			westNeighbor->render(false);
		}
	}
}
/*
void Room::setRotation( float deg ) {
	_rotation = deg;
	setModelMatrix();
}
*/
void Room::setPosition( int row, int col ) {
	_row = row;
	_col = col;
	setModelMatrix();
}

void Room::setModelMatrix() {
	glm::mat4 matrix = glm::translate( glm::mat4(), glm::vec3( roomWidth()*_col, 0.0f, roomWidth()*_row ) );
	matrix = glm::rotate(matrix, (float)_rotation, glm::vec3( 0.0f, 1.0f, 0.0f ) );
	ModelManagerClass::GetInstance()->SetModelMatrix( matrix, _name );
}

int Room::getColumn()
{
	return _col;
}

int Room::getRow()
{
	return _row;
}