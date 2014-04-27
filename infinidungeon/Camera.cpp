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
}

//Projection
void Camera::setProjection() {
	Projection = glm::perspective( 45.0f, 4.0f / 3.0f, 0.1f, 500.0f );
}

void Camera::setProjection( glm::mat4 a_mProjection ) {
	m_mProjection = a_mProjection;
}

//View
void Camera::setView() {
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

//Translation
void Camera::moveSideways( float a_fDisntance ) {
	m_mView = glm::translate( m_mView, glm::vec3( -a_fDisntance, 0.0f, 0.0f ) );
}
void Camera::moveForward( float a_fDisntance ) {
	m_mView = glm::translate( m_mView, glm::vec3( 0.0f, 0.0f, a_fDisntance ) );
}
void Camera::moveVertical( float a_fDisntance ) {
	m_mView = glm::translate( m_mView, glm::vec3( 0.0f, a_fDisntance, 0.0f ) );
}
void Camera::rotate( float a_fAngle ) {
	m_mView = glm::rotate( m_mView, a_fAngle, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}