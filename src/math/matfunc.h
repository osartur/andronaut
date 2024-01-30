/*********************************************************
   Various 3d transformation functions using matrices
   Copyright © 2021 Mark Craig

   https://www.youtube.com/MrMcSoftware
**********************************************************/

#ifndef _MATFUNC_H
#define _MATFUNC_H

#include "math/vec3.h"
#include "math/mat4.h"

mat4 Translate(const vec3 &t);
mat4 Scale(const vec3 &s);
mat4 Rotate(const float ang,const int type);
mat4 View(const vec3 &e,const vec3 &a,const vec3 &u);
mat4 PerspectiveProj(const float &ang,const float &zn,const float &zf);
mat4 ParallelProj(const float &xl,const float &xr,const float &yb,const float &yt,const float &zn,const float &zf);

#endif
