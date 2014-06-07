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

void Tm_identityTransform(TmTransform *out);
void Tm_transformApply(TmTransform t, TmVector in, TmVector *out);
void Tm_transformMultiply(TmTransform t1, TmTransform t2, TmTransform *out);
void Tm_transformInvertOrthoganal(TmTransform t, TmTransform *out);
float Tm_vectorDotProduct(TmVector a, TmVector b);
void Tm_vectorCrossProduct(TmVector a, TmVector b, TmVector *out);
void Tm_cameraTransform(TmVector at, TmVector up, TmVector position, TmTransform *out);

#ifdef __cplusplus
}
#endif