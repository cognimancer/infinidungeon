#ifndef _PLAYER_H
#define _PLAYER_H


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include "Camera.h"
#include "Room.h"
class Player
{
public:
	static Player* getInstance(); // Singleton Accessor
	void releaseInstance();	//Singleton Destructor
	
	Room* currentRoom;

	glm::vec3 getPosition() const {
		return _position;
	}

	void setSpeed( float speed );

	
	void move(glm::vec3 directions, glm::vec2 rotations,float frametime);

private:
	Player(void);
	~Player(void);
	Player( Player const& other); //Copy Constructor
	Player& operator=( Player const& other); // Copy Assignment Operator
	
	static Player* m_pInstance;//Singleton
	//Position
	glm::vec3 _position;

	void init();

	//Speed
	float _speed;

protected:
	//Camera* m_pCamera; //Pointer to the singleton of CameraClass
};


#endif
