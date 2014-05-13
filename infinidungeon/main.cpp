//#include <vld.h>
//#include <vector>
#include <GL\glew.h>
#include <GL\freeglut.h>
//#include <GL\freeglut_ext.h>
#include "View.h"
//#include <stdlib.h>
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

View *view;

int main( int argc, char **argv ) {
	glutInit( &argc, argv );
//	glutInitContextVersion( 3, 2 );
//	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );
	glutInitWindowSize( 1600, 900 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "infinidungeon" );
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glewExperimental = GL_TRUE;
	glewInit();

	view = new View();
	view->changeScreen( View::Dungeon );
    glutDisplayFunc( view->display );
	glutIdleFunc( view->idle );
	glutKeyboardFunc( view->keyboard );
	glutKeyboardUpFunc( view->keyboardUp );
	glutSpecialFunc( view->special );
	glutSpecialUpFunc( view->specialUp );
	glutMotionFunc( view->mouseMotion );
	glutPassiveMotionFunc( view->mousePassive );
	glutSetCursor( GLUT_CURSOR_NONE );

    glutMainLoop();

	delete view;

    return 0;
}
