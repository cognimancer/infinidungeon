infinidungeon
=============
Procedurally generated dungeon explorer

CONTROLS
========
move: WASD
rotate view: mouse
jump: space

FEATURES
========
Procedural room generation
-rooms are generated as needed (when the current room would otherwise have a door leading to nowhere)
-configurations are random, and different each time the program is run
-only the current room and the 1-4 surrounding rooms are rendered, but any other created rooms are still stored
Lighting
-angle of incidence
-inverse square law
-light source follows the camera
Physics
-gravity
-rudimentary collision detection
Full Screen support for a fully immersive experience!

KNOWN ISSUES
============
There's currently a problem with the T-shaped room rendering as an L-shaped room. Therefore it is possible to walk through some walls, and some doors may lead to the 'backside' of a room.
The room generation algorithm isn't the best... if your dungeon isn't infinite, reload and explore a new one!
