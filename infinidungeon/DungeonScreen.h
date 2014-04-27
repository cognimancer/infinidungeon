#ifndef DUNGEONCREEN_H
#define DUNGEONSCREEN_H

#include "AbstractScreen.h"
#include "Cube.h"

class DungeonScreen : public AbstractScreen {
private:
	float initialTime;
	float finalTime;
	Cube *_shape;
	bool _moveForward;
	bool _moveBackward;
	bool _moveRight;
	bool _moveLeft;
	bool _rotateRight;
	bool _rotateLeft;

public:
	DungeonScreen( View *view );
	DungeonScreen( const DungeonScreen &other );
	DungeonScreen &operator=( const DungeonScreen &other );
	~DungeonScreen();
	
	// glut I/O functions
	void display();
	void idle();
	void keyboard( unsigned char key, int x, int y );
	void keyboardUp( unsigned char key, int x, int y );
	void special( int key, int x, int y );
	void specialUp( int key, int x, int y );
};

#endif