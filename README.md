infinidungeon
=============
Procedurally generated dungeon explorer

CONTROLS
--------
* move: WASD
* rotate view: mouse
* jump: space
* fullscreen: f

FEATURES
--------
* Procedural room generation
  * rooms are generated as needed (when the current room would otherwise have a door leading to nowhere)
  * configurations are random, and different each time the program is run
  * only the current room and the 1-4 surrounding rooms are rendered, but any other created rooms are still stored
* Lighting
  * angle of incidence
  * inverse square law
  * light source follows the camera
* Physics
  * gravity
  * Collision Prevention (TM)
* Full Screen support for a fully immersive experience!