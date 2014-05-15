#include "Camera.h"
//  Camera
Camera *Camera::m_pInstance = nullptr;
Camera* Camera::getInstance() {
	if(m_pInstance == nullptr) {
		m_pInstance = new Camera();
	}
	return m_pInstance;
}
Camera::Camera() { init(); }
Camera::Camera( Camera const& other ) {}
Camera& Camera::operator=( Camera const& other ) { return *this; }
Camera::~Camera() { release(); }
void Camera::releaseInstance() {
	if( m_pInstance != nullptr ) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//--- Non Standard Singleton Methods
void Camera::release() {
	//No pointers allocated, so nothing to do here
}

void Camera::init() {
	setProjection();
	setView();
	calculateProjection();

	brightness = 100.0f;
}

//Projection
void Camera::setProjection() {
	m_mProjection = glm::perspective( 60.0f, 16.0f / 9.0f, 0.1f, 500.0f );
}

void Camera::setProjection( glm::mat4 a_mProjection ) {
	m_mProjection = a_mProjection;
}

//View
void Camera::setView() {
	//_position = glm::vec3( 0.0f, 3.0f, 5.0f );
	_orientation = glm::quat( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	m_mView = glm::lookAt(
							glm::vec3( 0.0f, 0.0f, 5.0f ),
							glm::vec3( 0.0f, 0.0f, 0.0f ),
							glm::vec3( 0.0f, 1.0f, 0.0f )
							);
}

void Camera::setView( glm::mat4 a_mView ) {
	m_mView = a_mView;
}

//MVP
glm::mat4 Camera::calculateProjection( glm::mat4 a_mModel ) {
	m_mMVP = m_mProjection * m_mView * a_mModel;
	return m_mMVP;
}

glm::mat4 Camera::getMVP() {
	return m_mMVP;
}

/*
void Camera::setSpeed( float speed ) {
	_speed = speed;
}
*/

// http://stackoverflow.com/questions/19738805/opengl-camera-control-with-arrow-keys
// modified to eliminate y-axis movement with forward/backward
//void Camera::move( glm::vec3 directions, glm::vec2 rotations, float frametime ) 
void Camera::move(glm::vec3 currentPosition)
{
	

    auto camera_roll_direction = _orientation * glm::vec3(0, 0, -1);
    auto camera_pitch_direction = _orientation * glm::vec3(-1, 0, 0);
	//auto tmp = _orientation * glm::vec3( 0, 0, -1 );
	//tmp.y = 0;
	//tmp = glm::normalize( tmp );
	



    m_mView = glm::lookAt(currentPosition, currentPosition + camera_roll_direction,
                        glm::cross(camera_roll_direction, camera_pitch_direction));
	
}

glm::quat Camera::getOrientation( glm::vec2 rotations)
{
	auto pitch = glm::quat(glm::vec3(-rotations.y, 0, 0.f));
    auto yaw = glm::quat(glm::vec3(0, -rotations.x, 0.f));

    _orientation = glm::normalize(yaw * _orientation * pitch);

	return _orientation;
}