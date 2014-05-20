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

	// calculate position
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
		getCurrentRoom();
		std::cout << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
	}

	// collision and room changing
	double roomRadius = Room::roomWidth() / 2;
	double innerRadius = (Room::roomWidth() - 16.0) / 2;
	double exitRadius = 2.3;
	double distX = _position.x - currentRoom->getColumn() * Room::roomWidth();
	double distY = _position.z - currentRoom->getRow() * Room::roomWidth();
	if( distX > innerRadius ) { // past east wall
		if( !currentRoom->exitEast || distY >= exitRadius || distY <= -exitRadius ) {
			// collision - stay at east wall
			_position.x = currentRoom->getColumn() * Room::roomWidth() + innerRadius;
		} else if( distX > roomRadius ) {
			// moved to east room
			currentRoom = currentRoom->east;
			std::cout << "moved east to room " << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
		} // else in east hallway
	}
	if( distX < -innerRadius ) { // past west wall
		if( !currentRoom->exitWest || distY >= exitRadius || distY <= -exitRadius ) {
			// collision - stay at west wall
			_position.x = currentRoom->getColumn() * Room::roomWidth() - innerRadius;
		} else if( distX < -roomRadius ) {
			// moved to west room
			currentRoom = currentRoom->west;
			std::cout << "moved west to room " << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
		} // else in west hallway
	}
	if( distY > innerRadius) { // past north wall
		if( !currentRoom->exitNorth || distX >= exitRadius || distX <= -exitRadius ) {
			// collision - stay at north wall
			_position.z = currentRoom->getRow() * Room::roomWidth() + innerRadius;
		} else if( distY > roomRadius ) {
			// moved to north room
			currentRoom = currentRoom->north;
			std::cout << "moved north to room " << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
		} // else in north hallway
	}
	if( distY < -innerRadius) { // past south wall
		if( !currentRoom->exitSouth || distX >= exitRadius || distX <= -exitRadius ) {
			// collision - stay at south wall
			_position.z = currentRoom->getRow() * Room::roomWidth() - innerRadius;
		} else if( distY < -roomRadius ) {
			// moved to south room
			currentRoom = currentRoom->south;
			std::cout << "moved south to room " << currentRoom->getColumn() << "," << currentRoom->getRow() << std::endl;
		} // else in south hallway
	}
	
	// move camera
	Camera::getInstance()->move(_position, _orientation);
}

void Player::setCurrentRoom(Room* givenRoom)
{
	currentRoom = givenRoom;
}

Room* Player::getCurrentRoom()
{
	return currentRoom;
}

