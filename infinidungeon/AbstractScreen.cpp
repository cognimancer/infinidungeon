#include "AbstractScreen.h"

AbstractScreen::AbstractScreen( View *view ) : _view( view ) {
	_shader = InitShader( "shaders/vshader.glsl", "shaders/fshader.glsl" );
	glutPostRedisplay();
}

AbstractScreen::AbstractScreen( const AbstractScreen &other ) : 
		_view( other._view ),
		_shader( other._shader ) {
	glutPostRedisplay();
}

AbstractScreen &AbstractScreen::operator=( const AbstractScreen &other ) {
	if( this != &other ) {
		_view = other._view;
		_shader = other._shader;
		glutPostRedisplay();
	}
	return *this;
}

AbstractScreen::~AbstractScreen() {}

void AbstractScreen::printText( int x, int y, std::string String ) {
    glUseProgram( _shader );
	glProgramUniformMatrix4fv( _shader, glGetUniformLocation( _shader, "ortho" ), 1, false,
		Ortho2D( -320.0f, 320.0f, -240.0f, 240.0f ) );
	glProgramUniformMatrix4fv( _shader, glGetUniformLocation( _shader, "world" ), 1, true,
		Translate( 0.0f, 0.0f, 0.0f ) );
	glProgramUniform4f( _shader, glGetUniformLocation( _shader, "dColor" ), 1.0f, 1.0f, 1.0f, 1.0f );
    glRasterPos2i( x, y );
    for( unsigned int i = 0; i < String.size(); ++i ) glutBitmapCharacter( GLUT_BITMAP_9_BY_15, String[i] );
}