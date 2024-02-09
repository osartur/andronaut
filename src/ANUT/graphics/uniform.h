#if not defined(ANUT_UNIFORM_H)
#define ANUT_UNIFORM_H
#include "ANUT/ANUT_math.h"

inline void SetVec4Uniform(int uniform_location, const vec4& v)
{
	glUniform4fv(uniform_location, 1, (float*) &v);
}

inline void SetMat4Uniform(int uniform_location, const mat4& m)
{
	glUniformMatrix4fv(uniform_location, 1, false, (float*) &m);
}

#endif
