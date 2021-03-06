#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H

#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
//#include <GL\freeglut_ext.h>
#include "AngelShaderCompiler.h"
#include "View.h"

// Abstract class for screens. Implementing classes are strategies for the View
// to change its display and input behavior.
class AbstractScreen {
protected:
	View *_view; // reference to the view to change screens if necessary
	GLuint _shader; // GL shader program

public:
	AbstractScreen( View *view );
	AbstractScreen( const AbstractScreen &other );
	AbstractScreen &operator=( const AbstractScreen &other );
	virtual ~AbstractScreen();

	// glut display function
	virtual void display() = 0;

	// glut idle function
	virtual void idle() = 0;

	// glut keyboard function
	virtual void keyboard( unsigned char key, int x, int y ) = 0;

	// glut keyboard up function
	virtual void keyboardUp( unsigned char key, int x, int y ) = 0;

	// glut special keyboard function
	virtual void special( int key, int x, int y ) = 0;

	// glut special keyboard up function
	virtual void specialUp( int key, int x, int y ) = 0;

	// glut mouse motion function (mouse moved while button pressed)
	virtual void mouseMotion( int x, int y ) = 0;

	// glut mouse passive motion function (mouse moved with no button pressed)
	virtual void mousePassive( int x, int y ) = 0;

protected:
	// prints the string to the screen starting at the given coordinates
	void printText( int x, int y, std::string String );
};

#endif