#ifndef VIEW_H
#define VIEW_H

class AbstractScreen;

// The View encapsulates glut I/O. It uses a strategy pattern to switch
// the I/O functions according to which screen is being displayed.
class View {
public:
	static const enum ViewID { Title, Dungeon };
private:
	// The Screen that is currently being displayed
	static AbstractScreen *currentInstance;

public:
	View();
	View( const View &other );
	View &operator=( const View &other );
	~View();
	
	// switch to a different screen (destroys the current screen and creates a new one)
	void changeScreen( ViewID screen );
	
	// glut I/O functions. These static functions call the corresponding
	// member functions of the current screen.
	static void display();
	static void idle();
	static void keyboard( unsigned char key, int x, int y );
	static void keyboardUp( unsigned char key, int x, int y );
	static void special( int key, int x, int y );
	static void specialUp( int key, int x, int y );
};

#endif