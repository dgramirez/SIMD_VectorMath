/**
* @file tMath.h <{184B652E-5B6F-44CC-99D0-2936EDFF9EFF}>
* 
* This file, along with "tMath.cpp", is a small minor project to convert my
* "EngineMath.h" and "EngineMath.cpp" into SIMD. There will be minor changes
* from the EngineMath Library to fit my style.
* 
* There has also been a few functions included from my Graphics I 
* (Fast Inverse, Perspective)
* and Engine Development Class.
* (LookAt)
* Due to this, it is not part of the check that EngineMath provides.
*/


#ifndef __tMath_h
#define __tMath_h

//Includes
#include <xmmintrin.h>
#include <array>

#pragma region (vec4) VECTOR 4 FUNCTIONS
typedef __m128 vec4;

//Helper Functions
vec4 vec4_fabs(const vec4& v);
bool vec4_isequal(const vec4& v1, const vec4& v2);
bool vec4_iszero(const vec4& v);
float deg_to_rad(float deg);
float rad_to_deg(float rad);

//Vec4 Simple Vector Math
vec4 vec4_add(const vec4& v1, const vec4& v2);
vec4 vec4_sub(const vec4& v1, const vec4& v2);
vec4 vec4_mul(const vec4& v, const float& scalar);
vec4 vec4_negate(const vec4& v);
vec4 vec4_max(const vec4& v1, const vec4& v2);
vec4 vec4_min(const vec4& v1, const vec4& v2);
vec4 vec4_avg(const vec4& v1, const vec4& v2);
float vec4_length2(const vec4& v);
float vec4_length(const vec4& v);
float vec4_component(vec4 v1, vec4 v2);

//Vec4 Vector Math
float vec4_dot(const vec4& v1, const vec4& v2);
vec4 vec4_cross(const vec4& v1, const vec4& v2);
vec4 vec4_normalize(const vec4& v);
vec4 vec4_homogenize(const vec4& v);
float vec4_anglebetween(vec4 v1, vec4 v2);
vec4 vec4_project(vec4 v1, vec4 v2);
vec4 vec4_reflect(vec4 v1, vec4 v2);
#pragma endregion

#pragma region (mat4) MATRIX 4x4 FUNCTIONS
using mat4 = std::array<vec4, 4>;

//Helper Functions
bool mat4_isequal(const mat4& m1, const mat4& m2);
bool mat4_iszero(const mat4& m);

//Mat4 Matrices
mat4 mat4_zero();
mat4 mat4_identity();
mat4 mat4_translation(const float& x, const float& y, const float& z);
mat4 mat4_scale(const float& x, const float& y, const float& z);
mat4 mat4_rotation_x(const float& rad);
mat4 mat4_rotation_y(const float& rad);
mat4 mat4_rotation_z(const float& rad);
mat4 mat4_transpose(mat4 m);
mat4 mat4_perspective(const float &fov_rad, const float &aspect_ratio_reciprocal, const float &n, const float &f);

//Mat4 Matrix Math
mat4 mat4_negate(const mat4& m);
mat4 mat4_add(const mat4& m1, const mat4& m2);
mat4 mat4_sub(const mat4& m1, const mat4& m2);
mat4 mat4_mul(const mat4& m, const float& scalar);
mat4 mat4_mul(const mat4& m1, mat4 m2);
vec4 vec4_mul(const mat4& m, const vec4& v);
vec4 vec4_mul(const vec4& v, mat4 m);

//Determinants and Inverses
float mat4_determinant(const mat4& m);
mat4 mat4_inverse(const mat4& m);
vec4 mat4_inverse_fast(const mat4& m);

//More Mat4 Matrix Math!
mat4 vec4_lookat(vec4 pos, vec4 eye, vec4 up);
#pragma endregion

#endif // __tMath_h
