#ifndef _PLAYER_H
#define _PLAYER_H

#include "Camera.h"
#include "Room.h"
class Player
{
public:
	static Player* getInstance(); // Singleton Accessor
	void releaseInstance();	//Singleton Destructor

	void setCurrentRoom(Room* givenRoom);
	Room* getCurrentRoom();

	glm::vec3 getPosition() const {
		return _position;
	}

	void setSpeed( float speed );
	
	
	void move(glm::vec3 directions, glm::vec2 rotations, float frametime, bool sprinting = false, bool jump = false);

private:
		
	Room* currentRoom;
	Player(void);
	~Player(void);
	Player( Player const& other); //Copy Constructor
	Player& operator=( Player const& other); // Copy Assignment Operator
	
	static Player* m_pInstance;//Singleton
	//Position
	glm::vec3 _position;
	glm::vec3 _prevPosition;
	//Orientation
	glm::quat _orientation;

	void init();

	//Speed
	float _speed;

protected:
	//Camera* m_pCamera; //Pointer to the singleton of CameraClass
};


#endif
