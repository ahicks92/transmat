transmat
========

A tiny matrix transformation library in ANSI C

The motivation for this library is simple.  After spending 48 hours working out how transformation matrices work for the second time in my life, I wanted something I could use everywhere.  Because it's C, it runs everywhere and can be integrated into everything.  I have done my best to conform to the C standard, and as far as I am aware this library invokes no undefined behavior.

Currently, the library supports matrix multiplication and applying transforms to vectors, inverting a matrix composed of rotations and translations, and building a camera matrix from at, up, and position vectors.  I will add more as I need them in other projects.

Note that the camera transformation function can easily be used to build a world matrix for an object.  To do so, invert the result you get back from it.

A note on convention: there is much confusion around the internet as to what means what.  This library follows the OpenGL conventions, which are summarized heree.

- Coordinate system is right handed.

- (0, 0, -1) represents forward, (0, 1, 0) represents up, and (1, 0, 0) represents right.

- Transformations are applied to column vectors.  That is, this library uses post-multiplication.

For more information on the different conventions, see [here](http://seanmiddleditch.com/journal/2012/08/matrices-handedness-pre-and-post-multiplication-row-vs-column-major-and-notations/).

The included CMakeLists.txt is intensionally minimalistic.  This allows one to simply use `add_subdirectory` and the submodule capabilities of git or another version control systems to integrate into your project.