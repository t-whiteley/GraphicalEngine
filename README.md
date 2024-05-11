My optimised OOP implementation of a graphics engine, low level and works in the terminal command line.

Implemented all stages of the graphics engine transformations.

1. Objects built out of triangle meshes in respective object spaces.
2. Objects transformed by translation/rotation to their space in the world space.
3. Camera is created and added to the world space.
4. Camera is centered at its own origin and pointed down -z, all objects transformed relative to the camera direction and position.
5. The canonical viewing volume is constructed from the camera space objects.
6. x and y coordinates are obtained in the viewport transform of the canonical viewing volume.

All necessary linear algebra and graphical transformations are self implemented, no external dependencies (other than sfml, for a better display)

Implementation note:
* graphicalengine/ is the directory containing the most current model
* there are two main() implmentations, one for a simple cross platform terminal based engine
* and an implementation assuming you have a path to the SFML library
* each main() has a comment which describes how I compile the code, make sure to change the path to your SFML library.