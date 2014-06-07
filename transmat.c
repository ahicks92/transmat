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

#include "transmat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

/**This is a matrix transformation library adequate for Libaudioverse's purposes**/

void identityTransform(TmTransform *out) {
	memset(out->mat, 0, sizeof(TmTransform));
	out->mat[0][0] = 1.0f;
	out->mat[1][1] = 1.0f;
	out->mat[2][2] = 1.0f;
	out->mat[3][3]=1.0f;
}

void transformApply(TmTransform trans, TmVector in, TmVector *out) {
	//we're multiplying a 3x3 by a 3x1. Output is therefore 3x1.
	for(int row = 0; row < 4; row++) {
		out->vec[row] = in.vec[0]*trans.mat[row][0]+in.vec[1]*trans.mat[row][1]+in.vec[2]*trans.mat[row][2]+in.vec[3]*trans.mat[row][3];
	}
}

void transformMultiply(TmTransform t1, TmTransform t2, TmTransform *out) {
	memset(out->mat, 0, sizeof(float)*16); //make sure it's clear so we can add to it directly.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			for(int k = 0; k < 4; k++) {	
				out->mat[i][j] += t1.mat[i][k]*t2.mat[k][j];
			}
		}
	}
}

void transformTranspose(TmTransform t, TmTransform *out) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			out->mat[i][j] = t.mat[j][i];
		}
	}
}

void transformInvertOrthoganal(TmTransform t, TmTransform *out) {
	TmTransform tmp = {0};
	TmVector trans = {0};
	trans.vec[0] = -1*t.mat[0][3];
	trans.vec[1] = -1*t.mat[1][3];
	trans.vec[2] = -1*t.mat[2][3];
	trans.vec[3] = 0.0f; //turn off the translation.  Oddly, this is what we want here.
	identityTransform(out);
	TmTransform rot;
	rot = t;
	rot.mat[0][3]=0;
	rot.mat[1][3]=0;
	rot.mat[2][3]=0;
	transformTranspose(rot, out); //gives us an inverted rotation.
	transformApply(*out, trans, &trans); //gives us the inverted translation component.
	//now, copy in the inverted translation.
	out->mat[0][3] = trans.vec[0];
	out->mat[1][3] = trans.vec[1];
	out->mat[2][3] = trans.vec[2];
}

float vectorDotProduct(TmVector a, TmVector b) {
	return a.vec[0]*b.vec[0]+a.vec[1]*b.vec[1]+a.vec[2]*b.vec[2];
}

void vectorCrossProduct(TmVector a, TmVector b, TmVector *out) {
	out->vec[0] = a.vec[1]*b.vec[2]-a.vec[2]*b.vec[1];
	out->vec[1]=a.vec[2]*b.vec[0]-a.vec[0]*b.vec[2];
	out->vec[2] = a.vec[0]*b.vec[1]-a.vec[1]*b.vec[0];
}

void cameraTransform(TmVector at, TmVector up, TmVector position, TmTransform *out) {
	TmVector cy = {.vec = {up.vec[0], up.vec[1], up.vec[2]}};
	TmVector cz = {.vec = {-at.vec[0], -at.vec[1], -at.vec[2]}};
	TmVector cx;
	//x is z cross y.
	//but we negated z, so it's actually y cross z.
	vectorCrossProduct(cy, cz, &cx);
	//figure out what we need to do with translation.
	float tx, ty, tz;
	tx = -vectorDotProduct(cx, position);
	ty = -vectorDotProduct(cy, position);
	tz = -vectorDotProduct(cz, position);
	//we now put these into out.
	for(int i = 0; i < 3; i++) {
		out->mat[0][i] = cx.vec[i];
		out->mat[1][i] = cy.vec[i];
		out->mat[2][i] = cz.vec[i];
		out->mat[3][i] = 0;
	}
	//and the translation components, computed above:
	out->mat[0][3] = tx;
	out->mat[1][3] = ty;
	out->mat[2][3] = tz;
	out->mat[3][3] = 1;
}
