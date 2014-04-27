#ifndef CUBE_H
#define CUBE_H
#include "DisplayObject.h"

class Cube : public DisplayObject {
private:
	glm::vec3 *_points;
public:
	Cube() : DisplayObject(), _points( new glm::vec3[18] ) { init(); }
	void init() {
		DisplayObject::init();

		_points[0] = glm::vec3( -5.0f, -5.0f, -50.0f );
		_points[1] = glm::vec3( 5.0f, -5.0f, -50.0f );
		_points[2] = glm::vec3( 5.0f, 5.0f, -50.0f );
		_points[3] = glm::vec3( -5.0f, 5.0f, -50.0f );
		_points[4] = glm::vec3( -5.0f, -5.0f, -50.0f );
		_points[5] = glm::vec3( -5.0f, -5.0f, -55.0f );
		_points[6] = glm::vec3( 5.0f, -5.0f, -50.0f );
		_points[7] = glm::vec3( 5.0f, -5.0f, -55.0f );
		_points[8] = glm::vec3( 5.0f, 5.0f, -50.0f );
		_points[9] = glm::vec3( 5.0f, 5.0f, -55.0f );
		_points[10] = glm::vec3( -5.0f, 5.0f, -50.0f );
		_points[11] = glm::vec3( -5.0f, 5.0f, -55.0f );
		_points[12] = glm::vec3( -5.0f, -5.0f, -50.0f );
		_points[13] = glm::vec3( -5.0f, -5.0f, -55.0f );
		_points[14] = glm::vec3( 5.0f, -5.0f, -55.0f );
		_points[15] = glm::vec3( 5.0f, 5.0f, -55.0f );
		_points[16] = glm::vec3( -5.0f, 5.0f, -55.0f );
		_points[17] = glm::vec3( -5.0f, -5.0f, -55.0f );
		glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( glm::vec3 ), _points, GL_STATIC_DRAW );
	}

	void render() {
		DisplayObject::render();
		
		GLuint mvp = glGetUniformLocation( _shader, "mvp" );
		glProgramUniformMatrix4fv( _shader, mvp, 1, false, glm::value_ptr( Camera::getInstance()->calculateProjection() ) );

		glDrawArrays( GL_LINE_LOOP, 0, 18 );
	}
};

#endif