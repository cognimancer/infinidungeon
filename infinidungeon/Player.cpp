#include "Player.h"

float groundLevel = 3.0f;
float gravity = 0.04f;
float zVelocity = 0.0f;

#pragma region Instance
Player *Player::m_pInstance = nullptr;
Player* Player::getInstance() {
	if(m_pInstance == nullptr) {
		m_pInstance = new Player();
	}
	return m_pInstance;
}
void Player::releaseInstance() {
	if( m_pInstance != nullptr ) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

#pragma endregion


Player::Player(void){init();}

Player::~Player(void)
{
}

Player::Player( Player const& other ) {}

Player& Player::operator=( Player const& other ) { return *this; }

void Player::init(){
	//m_pCamera = Camera::getInstance();
	_position = glm::vec3( 0.0f, 100, 0.0f );
	_orientation = glm::quat( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	_speed = 3.0f;
};

void Player::setSpeed( float speed ) {
	_speed = speed;
}

// http://stackoverflow.com/questions/19738805/opengl-camera-control-with-arrow-keys
// modified to eliminate y-axis movement with forward/backward
void Player::move(glm::vec3 directions, glm::vec2 rotations, float frametime, bool sprinting, bool jump) {

	// calculate orientation
	auto pitch = glm::quat(glm::vec3(-rotations.y, 0, 0.f));
    auto yaw = glm::quat(glm::vec3(0, -rotations.x, 0.f));
    _orientation = glm::normalize(yaw * _orientation * pitch);

	auto camera_roll_direction = _orientation * glm::vec3(0, 0, -1);
    auto camera_pitch_direction = _orientation * glm::vec3(-1, 0, 0);
	auto tmp = camera_roll_direction;
	tmp.y = 0;
	tmp = glm::normalize( tmp );

	float delta = _speed * (sprinting ? 3.0f : 1.0f);
	// jumping
	//if (_position.y == groundLevel && jump) _position.y = 10;
	if (_position.y == groundLevel && jump) zVelocity += .4;
	// gravity
	//if (_position.y > groundLevel) _position.y -= gravity;
	if (_position.y > groundLevel) zVelocity -= gravity;

	// forward/backward move - only xz could be affected
    _position += directions[0] * tmp * frametime * delta;
    // left and right strafe - only xz could be affected    
    _position += directions[1] * camera_pitch_direction * frametime * delta;
    // up and down flying - only y-axis could be affected
    _position.y += zVelocity;//directions[2] * frametime * delta;
	if (_position.y < groundLevel) {
		_position.y = groundLevel;
		zVelocity = 0;
	}
	// restrict camera to room dimensions
	//FIXME temp disabled to demo moving between rooms - should be moved to Player or Room
	//	_position.x = glm::clamp(_position.x, -22.0f, 22.0f);
	//	_position.z = glm::clamp(_position.z, -21.0f, 21.0f);
	//getCurrentRoom();
	//std::cout << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
	Camera::getInstance()->move(_position, _orientation);
}

void Player::setCurrentRoom(Room* givenRoom)
{
	currentRoom = givenRoom;
}

Room* Player::getCurrentRoom()
{
	double roomRadius = (currentRoom->roomWidth()/2);
	glm::vec3 currentRoomCenter = glm::vec3(
		(currentRoom->getColumn() * currentRoom->roomWidth()) - roomRadius,
		0,
		(currentRoom->getRow() * currentRoom->roomWidth()) - roomRadius);
	double distance = sqrt(((currentRoomCenter.x - _position.x)*(currentRoomCenter.x - _position.x))+((currentRoomCenter.z - _position.z)*(currentRoomCenter.z - _position.z)));
	if (distance > roomRadius)
	{
		if(_position.x-currentRoomCenter.x > roomRadius)
		{//east
			return currentRoom = currentRoom->east;
		}
		else if (_position.x-currentRoomCenter.x < roomRadius)
		{//west
			return currentRoom = currentRoom->west;
		}
		else if (_position.z-currentRoomCenter.z > roomRadius)
		{//north
			return currentRoom = currentRoom->north;
		}
		else if (_position.z-currentRoomCenter.z < roomRadius)
		{//south
			return currentRoom = currentRoom->south;
		}
	}
	return currentRoom;
}

