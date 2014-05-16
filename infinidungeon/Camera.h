#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

class Camera {
public:
	static Camera* getInstance(); // Singleton Accessor
	void releaseInstance();	//Singleton Destructor

	glm::vec3 getPosition() const {
		return _position;
	}
	
	//Visibility / Light Brightness
	float brightness;

	//void move(glm::vec3 directions, glm::vec2 rotations, float frametime);
	
	void move(glm::vec3 currentPosition, glm::quat currentOrientation);

	//Projection
	void setProjection();
	void setProjection( glm::mat4 a_mProjection );
	__declspec( property( put = setProjection ) ) glm::mat4 Projection;

	//View
	void setView();
	void setView( glm::mat4 a_mView );
	__declspec( property( put = setView ) ) glm::mat4 View;
	
	//MVP
	glm::mat4 calculateProjection( glm::mat4 a_mModel = glm::mat4( 1.0f ) );
	glm::mat4 getMVP();
	__declspec( property( get = getMVP ) ) glm::mat4 VMP;

private:
	Camera( void ); // Constructor
	Camera( Camera const& other); //Copy Constructor
	Camera& operator=( Camera const& other); // Copy Assignment Operator
	~Camera( void ); //Destructor
	
	void release( void );// Releases the memory

	void init( void ); //Init the values

	static Camera* m_pInstance;//Singleton

	//Projection
	glm::mat4 m_mProjection;
	//View
	glm::mat4 m_mView;
	//MVP
	glm::mat4 m_mMVP;

	//Position
	glm::vec3 _position;
	//Orientation
	glm::quat _orientation;
};


#endif //_CAMERA_H