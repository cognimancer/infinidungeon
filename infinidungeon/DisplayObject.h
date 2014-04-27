#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <GL\glew.h>
#include "AngelShaderCompiler.h"
#include "Camera.h"

// Abstract class for objects that are displayed on the screen.
// It handles common rendering activities.
class DisplayObject {
protected:
	GLuint _vao;
	GLuint _buffer;
	GLuint _shader;

public:
	DisplayObject();
	DisplayObject( const DisplayObject &other );
	DisplayObject &operator=( const DisplayObject &other );
	virtual ~DisplayObject();

	// Finds the point on the DisplayObject which is closest to the given point
//	virtual vec2 closestPoint( const vec2 &other ) const = 0;
	// Detects and resolves collisions
//	virtual bool handleCollision( Ball &ball, float dt ) = 0;
	// Displays the object on the screen
	virtual void render();

protected:
	virtual void init();
};

#endif