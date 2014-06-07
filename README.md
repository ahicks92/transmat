transmat
========

A tiny matrix transformation library in ANSI C

The motivation for this library is simple.  After spending 48 hours working out how transformation matrices work for the second time in my life, I wanted something I could use everywhere.  Because it's C, it runs everywhere and can be integrated into everything.  I have done my best to conform to the C standard, and as far as I am aware this library invokes no undefined behavior.

Currently, the library supports matrix multiplication and applying transforms to vectors, inverting a matrix composed of rotations and translations, and building a camera matrix from at, up, and position vectors.  I will add more as I need them in other projects.

The included CMakeLists.txt is intensionally minimalistic.  This allows one to simply use `add_submdirectory` and the submodule capabilities of git or another version control systems to integrate into your project.