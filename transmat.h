/**This file is part of transmat, a tiny ANSi C library for matrix transformations.
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TmTransform {
	float mat[4][4];
} TmTransform;
typedef struct TmVector {
	float vec[4];
} TmVector;

/**This library uses pre multiplication for the transformation application step.

In terms of memory, matrices are layed out across the rows and down; that is, using the standard notion mrc (m11 is the top left, m41 is the bottom left):
{m11, m12, m13, m14, ..., m41, m42, m43, m44}

Vectors are arrays of 4 floats, {x, y, z, w}.
When w=0, a vector represents a direction; when w=1, a vector represents a position.
Another way to put this is that w is a boolean switch which turns off and on the translation component of any transformation.  For most purposes, set w to 1.
Note that this is an oversimplification: w is important in the realm of graphical projection, but those portions of the pipeline are likely to be written on your GPU as shaders, and a full discussion of w is too verbose for this comment.

To actually set a vector, set its .vec attribute appropriately. None of these functions allocate for you but instead modify a TmTransform in place.
*/

void identityTransform(TmTransform *out);
void transformApply(TmTransform t, TmVector in, TmVector *out);
void transformMultiply(TmTransform t1, TmTransform t2, TmTransform *out);
void transformInvertOrthoganal(TmTransform t, TmTransform *out);
float vectorDotProduct(TmVector a, TmVector b);
void vectorCrossProduct(TmVector a, TmVector b, TmVector *out);
void cameraTransform(TmVector at, TmVector up, TmVector position, TmTransform *out);

#ifdef __cplusplus
}
#endif