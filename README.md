My OOP implementation of a graphics engine, low level and works in the terminal command line.

Implemented all stages of the graphics engine transformations.

1. Objects built out of triangle meshes in respective object spaces.
2. Objects transformed by translation/rotation to their space in the world space.
3. Camera is created and added to the world space.
4. Camera is centered at its own origin and pointed down -z, all objects transformed to this seperate space.
5. The canonical viewing voume is constructed from camera space.
6. x and y coordinates are obtained in the viewport transform of the canonical viewing volume.

All necessary linear algebra and graphical transformations are self implemented, no external dependencies.