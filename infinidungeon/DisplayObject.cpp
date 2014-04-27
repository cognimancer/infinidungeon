#include "DisplayObject.h"

DisplayObject::DisplayObject() : _vao( 0 ), _buffer( 0 ), _shader( 0 ) {}
DisplayObject::DisplayObject( const DisplayObject &other ) {} //TODO
DisplayObject &DisplayObject::operator=( const DisplayObject &other ) { return *this; } //TODO
DisplayObject::~DisplayObject() {
	//CleanUp VBO, Buffer and Shader Program
	glDeleteBuffers( 1, &_buffer );
	glDeleteProgram( _shader );
	glDeleteVertexArrays( 1, &_vao );
}

void DisplayObject::init() {
	// Create a vertex array object
    glGenVertexArrays( 1, &_vao );
    glBindVertexArray( _vao );

	// Create and initialize the object's buffer
    glGenBuffers( 1, &_buffer );
    glBindBuffer( GL_ARRAY_BUFFER, _buffer );
	// Loading the buffer is done by the child class

	// Load shaders and use the resulting shader program
	_shader = CompileShader( "shaders/vshader.glsl", "shaders/fshader.glsl" );
    glUseProgram( _shader );
	
	// Initialize the vertex position attribute from the vertex shader
    GLuint vPosition = glGetAttribLocation( _shader, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
}

void DisplayObject::render() {
	glUseProgram( _shader );
	glBindBuffer( GL_ARRAY_BUFFER, _buffer );

	// Initialize the vertex position attribute from the vertex shader.
    GLuint vPosition = glGetAttribLocation( _shader, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
	
	// Provide a default color.
	glProgramUniform4f( _shader, glGetUniformLocation( _shader, "dColor" ), 1.0f, 1.0f, 1.0f, 1.0f );
}
