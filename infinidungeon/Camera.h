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

	//Translate
	void moveSideways( float a_fDistance = 0.1f );
	void moveVertical( float a_fDistance = 0.1f );
	void moveForward( float a_fDistance = 0.1f );
	void rotate( float a_fAngle = 0.1f );
	
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
};


#endif //_CAMERA_H