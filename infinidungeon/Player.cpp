#include "Player.h"


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
	_speed = 3.0f;
};

void Player::setSpeed( float speed ) {
	_speed = speed;
}

void Player::move(glm::vec3 directions, glm::vec2 rotations,float frametime)
{
	glm::quat tempOrientation = Camera::getInstance()->getOrientation(rotations);
	auto camera_roll_direction = tempOrientation * glm::vec3(0, 0, -1);
    auto camera_pitch_direction = tempOrientation * glm::vec3(-1, 0, 0);
	auto tmp = tempOrientation * glm::vec3( 0, 0, -1 );
	tmp.y = 0;
	tmp = glm::normalize( tmp );

	// forward/backward move - only xz could be affected
    _position += directions[0] * tmp * frametime * _speed;
    // left and right strafe - only xz could be affected    
    _position += directions[1] * camera_pitch_direction * frametime * _speed;
    // up and down flying - only y-axis could be affected
    _position.y += directions[2] * frametime * _speed;

	Camera::getInstance()->move(_position);
	// restrict camera to room dimensions
	//FIXME temp disabled to demo moving between rooms - should be moved to Player or Room
	//	_position.x = glm::clamp(_position.x, -22.0f, 22.0f);
	//	_position.z = glm::clamp(_position.z, -21.0f, 21.0f);
}