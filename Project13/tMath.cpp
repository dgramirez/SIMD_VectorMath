#include "tMath.h"
#include <immintrin.h>

//CHANGABLE DEFINE
#define __USEEPSILON 1

//Static Variables
static const unsigned int vX = 3;
static const unsigned int vY = 2;
static const unsigned int vZ = 1;
static const unsigned int vW = 0;

static const unsigned int mX = 0;
static const unsigned int mY = 1;
static const unsigned int mZ = 2;
static const unsigned int mW = 3;

static const float PI = 3.14159265359f;
static const float PI_OVER_180 = 0.01745329251f;
static const float _180_OVER_PI = 57.2957795131f;

static const __m128 SIGN_MASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
static const __m128 ZERO = _mm_set1_ps(0.0f);
static const __m128 EPSILON = _mm_set1_ps(0.00001f);

//Static Matrix Indices
static const unsigned int  e11 =  0; static const unsigned int  e12 =  1; static const unsigned int  e13 =  2; static const unsigned int  e14 =  3;
static const unsigned int  e21 =  4; static const unsigned int  e22 =  5; static const unsigned int  e23 =  6; static const unsigned int  e24 =  7;
static const unsigned int  e31 =  8; static const unsigned int  e32 =  9; static const unsigned int  e33 = 10; static const unsigned int  e34 = 11;
static const unsigned int  e41 = 12; static const unsigned int  e42 = 13; static const unsigned int  e43 = 14; static const unsigned int  e44 = 15;


//Helper Functions
vec4 vec4_set(const float& x, const float& y, const float& z, const float& w) { return _mm_set_ps(x, y, z, w); }
vec4 vec4_set(const float& n) { return _mm_set1_ps(n); }
vec4 vec4_load(const float* n) { return _mm_load_ps(n); }
vec4 vec4_load1(const float* n) { return _mm_load1_ps(n); }
vec4 vec4_fabs(const vec4& v)
{
	return _mm_andnot_ps(SIGN_MASK, v);
}
bool vec4_isequal(const vec4& v1, const vec4& v2)
{
#if __USEEPSILON
	vec4 chk = _mm_cmple_ps(_mm_andnot_ps(SIGN_MASK, _mm_sub_ps(v1, v2)),EPSILON);
#else
	vec4 chk = _mm_cmpeq_ps(v1, v2);
#endif
	return chk.m128_u32[0] & chk.m128_u32[1] & chk.m128_u32[2] & chk.m128_u32[3];
}
bool vec4_iszero(const vec4& v)
{
#if __USEEPSILON
	vec4 chk = _mm_cmple_ps(_mm_andnot_ps(SIGN_MASK, v), EPSILON);
#else
	vec4 chk = _mm_cmpeq_ps(v, ZERO);
#endif
	return chk.m128_u32[0] & chk.m128_u32[1] & chk.m128_u32[2] & chk.m128_u32[3];
}
float deg_to_rad(float deg) { return deg * PI_OVER_180; }
float rad_to_deg(float rad) { return rad * _180_OVER_PI; }

//Vec4 Simple Vector Math
vec4 vec4_add(const vec4& v1, const vec4& v2)		{ return _mm_add_ps(v1, v2); }
vec4 vec4_sub(const vec4& v1, const vec4& v2)		{ return _mm_sub_ps(v1, v2); }
vec4 vec4_mul(const vec4& v, const float& scalar)	{ return _mm_mul_ps(v, _mm_set1_ps(scalar)); }
vec4 vec4_negate(const vec4& v)						{ return _mm_mul_ps(v, _mm_set1_ps(-1.0f)); }
vec4 vec4_max(const vec4& v1, const vec4& v2)		{ return _mm_max_ps(v1, v2); }
vec4 vec4_min(const vec4& v1, const vec4& v2)		{ return _mm_min_ps(v1, v2); }
vec4 vec4_avg(const vec4& v1, const vec4& v2)		{ return _mm_mul_ps(_mm_add_ps(v1, v2), _mm_set1_ps(0.5f)); }
float vec4_length2(const vec4& v)					{ return vec4_dot(v, v); }
float vec4_length(const vec4& v)					{ return _mm_sqrt_ss(_mm_set1_ps(vec4_length2(v))).m128_f32[0]; }
float vec4_component(vec4 v1, vec4 v2)				{ return vec4_dot(v1, vec4_normalize(v2)); }

//Vec4 Vector Math
float vec4_dot(const vec4& v1, const vec4& v2)
{
	vec4 save = _mm_mul_ps(v1, v2);
	return save.m128_f32[vX] + save.m128_f32[vY] + save.m128_f32[vZ] + save.m128_f32[vW];
}
vec4 vec4_cross(const vec4& v1, const vec4& v2)
{
	return _mm_set_ps(
		(v1.m128_f32[vY] * v2.m128_f32[vZ]) - (v1.m128_f32[vZ] * v2.m128_f32[vY]),
		(v1.m128_f32[vZ] * v2.m128_f32[vX]) - (v1.m128_f32[vX] * v2.m128_f32[vZ]),
		(v1.m128_f32[vX] * v2.m128_f32[vY]) - (v1.m128_f32[vY] * v2.m128_f32[vX]),
		0.0f);
}
vec4 vec4_normalize(const vec4& v)
{
	vec4 length = _mm_set1_ps(vec4_length2(v));
	if (vec4_iszero(length))
		return v;
	return _mm_div_ps(v, _mm_set1_ps(_mm_sqrt_ss(length).m128_f32[0]));
}
vec4 vec4_homogenize(const vec4& v)
{
	if (vec4_iszero(v))
		return v;
	return _mm_div_ps(v, _mm_set1_ps(v.m128_f32[vW]));
}
float vec4_anglebetween(vec4 v1, vec4 v2)
{
	vec4 length = _mm_set1_ps(vec4_length2(v1) * vec4_length2(v2));
	if (vec4_iszero(length))
		return 0;
	return _mm_acos_ps(_mm_set1_ps(vec4_dot(v1, v2) / _mm_sqrt_ss(length).m128_f32[0])).m128_f32[0];
}
vec4 vec4_project(vec4 v1, vec4 v2)
{
	vec4 norm_v2 = vec4_normalize(v2);
	return vec4_mul(norm_v2, vec4_dot(v1, norm_v2));
}
vec4 vec4_reflect(vec4 v1, vec4 v2)
{
	if (vec4_iszero(v2))
		return vec4_negate(v1);

	return vec4_negate(vec4_add(vec4_mul(vec4_project(v1, v2), -2.0f), v1));
}

//Helper Functions
bool mat4_isequal(const mat4& m1, const mat4& m2)
{
	return vec4_isequal(m1[mX], m2[mX]) && vec4_isequal(m1[mY], m2[mY]) && vec4_isequal(m1[mZ], m2[mZ]) && vec4_isequal(m1[mW], m2[mW]);
}
bool mat4_iszero(const mat4& m)
{
	return vec4_iszero(m[mX]) && vec4_iszero(m[mY]) && vec4_iszero(m[mZ]) && vec4_iszero(m[mW]);
}

//Mat4 Matrices
mat4 mat4_zero()
{
	mat4 m;
	m[mX] = _mm_set1_ps(0.0f);
	m[mY] = _mm_set1_ps(0.0f);
	m[mZ] = _mm_set1_ps(0.0f);
	m[mW] = _mm_set1_ps(0.0f);
	return m;
}
mat4 mat4_identity()
{
	mat4 m;
	m[mX] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	m[mY] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	m[mZ] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	m[mW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}
mat4 mat4_translation(const float& x, const float& y, const float& z)
{
	mat4 m;
	m[mX] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	m[mY] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	m[mZ] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	m[mW] = _mm_set_ps( x  ,  y  ,  z  , 1.0f);
	return m;
}
mat4 mat4_scale(const float& x, const float& y, const float& z)
{
	mat4 m;
	m[mX] = _mm_set_ps( x  , 0.0f, 0.0f, 0.0f);
	m[mY] = _mm_set_ps(0.0f,  y  , 0.0f, 0.0f);
	m[mZ] = _mm_set_ps(0.0f, 0.0f,  z  , 0.0f);
	m[mW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}
mat4 mat4_rotation_x(const float& rad)
{
	vec4 r = _mm_set1_ps(rad);
	float cos = _mm_cos_ps(r).m128_f32[0];
	float sin = _mm_sin_ps(r).m128_f32[0];

	mat4 m;
	m[mX] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	m[mY] = _mm_set_ps(0.0f, cos , -sin, 0.0f);
	m[mZ] = _mm_set_ps(0.0f, sin ,  cos, 0.0f);
	m[mW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}
mat4 mat4_rotation_y(const float& rad)
{
	vec4 r = _mm_set1_ps(rad);
	float cos = _mm_cos_ps(r).m128_f32[0];
	float sin = _mm_sin_ps(r).m128_f32[0];

	mat4 m;
	m[mX] = _mm_set_ps(cos , 0.0f, sin , 0.0f);
	m[mY] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	m[mZ] = _mm_set_ps(-sin, 0.0f, cos, 0.0f);
	m[mW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}
mat4 mat4_rotation_z(const float& rad)
{
	vec4 r = _mm_set1_ps(rad);
	float cos = _mm_cos_ps(r).m128_f32[0];
	float sin = _mm_sin_ps(r).m128_f32[0];

	mat4 m;
	m[mX] = _mm_set_ps(cos , -sin, 0.0f, 0.0f);
	m[mY] = _mm_set_ps(sin , cos , 0.0f, 0.0f);
	m[mZ] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	m[mW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	return m;
}
mat4 mat4_transpose(mat4 m)
{
	_MM_TRANSPOSE4_PS(m[mW], m[mZ], m[mY], m[mX]);
	return m;
}
mat4 mat4_perspective(const float& fov_rad, const float& aspect_ratio_reciprocal, const float& n, const float& f)
{
	vec4 fov = _mm_set1_ps(fov_rad * 0.5f);
	float yScale = 1.0f / _mm_tan_ps(fov).m128_f32[0];

	mat4 m;
	m[mX] = _mm_set_ps(yScale * aspect_ratio_reciprocal, 0, 0, 0);
	m[mY] = _mm_set_ps(0, yScale, 0, 0);
	m[mZ] = _mm_set_ps(0, 0, f / (f - n), 1);
	m[mW] = _mm_set_ps(0, 0, -(f*n)/(f-n), 0);

	return m;
}

//Mat4 Matrix Math
mat4 mat4_negate(const mat4& m)
{
	const vec4 neg1 = _mm_set1_ps(-1.0f);
	mat4 _m;
	_m[mX] = _mm_mul_ps(m[mX], neg1);
	_m[mY] = _mm_mul_ps(m[mY], neg1);
	_m[mZ] = _mm_mul_ps(m[mZ], neg1);
	_m[mW] = _mm_mul_ps(m[mW], neg1);
	return _m;
}
mat4 mat4_add(const mat4& m1, const mat4& m2)
{
	mat4 _m;
	_m[mX] = _mm_add_ps(m1[mX], m2[mX]);
	_m[mY] = _mm_add_ps(m1[mY], m2[mY]);
	_m[mZ] = _mm_add_ps(m1[mZ], m2[mZ]);
	_m[mW] = _mm_add_ps(m1[mW], m2[mW]);
	return _m;
}
mat4 mat4_sub(const mat4& m1, const mat4& m2)
{
	mat4 _m;
	_m[mX] = _mm_sub_ps(m1[mX], m2[mX]);
	_m[mY] = _mm_sub_ps(m1[mY], m2[mY]);
	_m[mZ] = _mm_sub_ps(m1[mZ], m2[mZ]);
	_m[mW] = _mm_sub_ps(m1[mW], m2[mW]);
	return _m;
}
mat4 mat4_mul(const mat4& m, const float& scalar)
{
	const vec4 _scalar = _mm_set1_ps(scalar);
	mat4 _m;
	_m[mX] = _mm_mul_ps(m[mX], _scalar);
	_m[mY] = _mm_mul_ps(m[mY], _scalar);
	_m[mZ] = _mm_mul_ps(m[mZ], _scalar);
	_m[mW] = _mm_mul_ps(m[mW], _scalar);
	return _m;
}
vec4 vec4_mul(const mat4& m, const vec4& v)
{
	return _mm_set_ps(vec4_dot(m[mX], v), vec4_dot(m[mY], v), vec4_dot(m[mZ], v), vec4_dot(m[mW], v));
}
vec4 vec4_mul(const vec4& v, mat4 m)
{
	_MM_TRANSPOSE4_PS(m[mW], m[mZ], m[mY], m[mX]);
	return _mm_set_ps(vec4_dot(m[mX], v), vec4_dot(m[mY], v), vec4_dot(m[mZ], v), vec4_dot(m[mW], v));
}
mat4 mat4_mul(const mat4& m1, mat4 m2)
{
	mat4 _m;
	_MM_TRANSPOSE4_PS(m2[mW], m2[mZ], m2[mY], m2[mX]);

	_m[mX] = _mm_set_ps(
		vec4_dot(m1[mX], m2[mX]),
		vec4_dot(m1[mX], m2[mY]),
		vec4_dot(m1[mX], m2[mZ]),
		vec4_dot(m1[mX], m2[mW])
	);

	_m[mY] = _mm_set_ps(
		vec4_dot(m1[mY], m2[mX]),
		vec4_dot(m1[mY], m2[mY]),
		vec4_dot(m1[mY], m2[mZ]),
		vec4_dot(m1[mY], m2[mW])
	);

	_m[mZ] = _mm_set_ps(
		vec4_dot(m1[mZ], m2[mX]),
		vec4_dot(m1[mZ], m2[mY]),
		vec4_dot(m1[mZ], m2[mZ]),
		vec4_dot(m1[mZ], m2[mW])
	);

	_m[mW] = _mm_set_ps(
		vec4_dot(m1[mW], m2[mX]),
		vec4_dot(m1[mW], m2[mY]),
		vec4_dot(m1[mW], m2[mZ]),
		vec4_dot(m1[mW], m2[mW])
	);

	return _m;
}

//Determinants and Inverses
static float mat3_determinant(  const float &e_11, const float &e_12, const float &e_13,
								const float &e_21, const float &e_22, const float &e_23,
								const float &e_31, const float &e_32, const float &e_33)
{
	//RETURN: The determinant of the 3x3 matrix
	return e_11 * (e_22 * e_33 - e_32 * e_23) - e_12 * (e_21 * e_33 - e_31 * e_23) + e_13 * (e_21 * e_32 - e_31 * e_22);
}
float mat4_determinant(const mat4& m)
{
	const float *p = &m[0].m128_f32[0];
	return *(p      ) * mat3_determinant(*(p + e22), *(p + e23), *(p + e24), *(p + e32), *(p + e33), *(p + e34), *(p + e42), *(p + e43), *(p + e44))
		-  *(p + e12) * mat3_determinant(*(p + e21), *(p + e23), *(p + e24), *(p + e31), *(p + e33), *(p + e34), *(p + e41), *(p + e43), *(p + e44))
		+  *(p + e13) * mat3_determinant(*(p + e21), *(p + e22), *(p + e24), *(p + e31), *(p + e32), *(p + e34), *(p + e41), *(p + e42), *(p + e44))
		-  *(p + e14) * mat3_determinant(*(p + e21), *(p + e22), *(p + e23), *(p + e31), *(p + e32), *(p + e33), *(p + e41), *(p + e42), *(p + e43));
}
mat4 mat4_inverse(const mat4& m)
{
	//Determinant
	vec4 det = _mm_set1_ps(mat4_determinant(m));
	if (vec4_iszero(det))
		return m;

	//Transposed Determinant Matrix
	const float* p = &m[mX].m128_f32[0];
	mat4 a_transposed;
	a_transposed[vX] =_mm_set_ps(
		 mat3_determinant(*(p + e22), *(p + e23), *(p + e24), *(p + e32), *(p + e33), *(p + e34), *(p + e42), *(p + e43), *(p + e44)),
		-mat3_determinant(*(p + e12), *(p + e13), *(p + e14), *(p + e32), *(p + e33), *(p + e34), *(p + e42), *(p + e43), *(p + e44)),
		 mat3_determinant(*(p + e12), *(p + e13), *(p + e14), *(p + e22), *(p + e23), *(p + e24), *(p + e42), *(p + e43), *(p + e44)),
		-mat3_determinant(*(p + e12), *(p + e13), *(p + e14), *(p + e22), *(p + e23), *(p + e24), *(p + e32), *(p + e33), *(p + e34))
	);
	a_transposed[vY] = _mm_set_ps(
		-mat3_determinant(*(p + e21), *(p + e23), *(p + e24), *(p + e31), *(p + e33), *(p + e34), *(p + e41), *(p + e43), *(p + e44)),
		 mat3_determinant(*(p + e11), *(p + e13), *(p + e14), *(p + e31), *(p + e33), *(p + e34), *(p + e41), *(p + e43), *(p + e44)),
		-mat3_determinant(*(p + e11), *(p + e13), *(p + e14), *(p + e21), *(p + e23), *(p + e24), *(p + e41), *(p + e43), *(p + e44)),
		 mat3_determinant(*(p + e11), *(p + e13), *(p + e14), *(p + e21), *(p + e23), *(p + e24), *(p + e31), *(p + e33), *(p + e34))
	);
	a_transposed[vZ] = _mm_set_ps(
		 mat3_determinant(*(p + e21), *(p + e22), *(p + e24), *(p + e31), *(p + e32), *(p + e34), *(p + e41), *(p + e42), *(p + e44)),
		-mat3_determinant(*(p + e11), *(p + e12), *(p + e14), *(p + e31), *(p + e32), *(p + e34), *(p + e41), *(p + e42), *(p + e44)),
		 mat3_determinant(*(p + e11), *(p + e12), *(p + e14), *(p + e21), *(p + e22), *(p + e24), *(p + e41), *(p + e42), *(p + e44)),
		-mat3_determinant(*(p + e11), *(p + e12), *(p + e14), *(p + e21), *(p + e22), *(p + e24), *(p + e31), *(p + e32), *(p + e34))
	);
	a_transposed[vW] = _mm_set_ps(
		-mat3_determinant(*(p + e21), *(p + e22), *(p + e23), *(p + e31), *(p + e32), *(p + e33), *(p + e41), *(p + e42), *(p + e43)),
		 mat3_determinant(*(p + e11), *(p + e12), *(p + e13), *(p + e31), *(p + e32), *(p + e33), *(p + e41), *(p + e42), *(p + e43)),
		-mat3_determinant(*(p + e11), *(p + e12), *(p + e13), *(p + e21), *(p + e22), *(p + e23), *(p + e41), *(p + e42), *(p + e43)),
		 mat3_determinant(*(p + e11), *(p + e12), *(p + e13), *(p + e21), *(p + e22), *(p + e23), *(p + e31), *(p + e32), *(p + e33))
	);

	//Return
	return mat4_mul(a_transposed, 1.0f/det.m128_f32[0]);
}
vec4 mat4_inverse_fast(const mat4& m)
{
	mat4 _m;
	const float* p = &m[0].m128_f32[0];

	//Transpose the 3x3 portion of the matrix
	_m[vX] = _mm_set_ps(*(p		 ), *(p + e21), *(p + e31), *(p + e14));
	_m[vY] = _mm_set_ps(*(p + e12), *(p + e22), *(p + e32), *(p + e24));
	_m[vZ] = _mm_set_ps(*(p + e13), *(p + e23), *(p + e33), *(p + e34));
	_m[vW] = _mm_set_ps(*(p + e41), *(p + e42), *(p + e43), *(p + e44));

	//Create Vector using the position vector from the matrix
	vec4 pos = m[vW];
	return vec4_negate(vec4_mul(pos, _m));
}

//More Mat4 Matrix Math!
mat4 vec4_lookat(vec4 pos, vec4 eye, vec4 up)
{
	mat4 m;
	m[vZ] = vec4_normalize(_mm_sub_ps(eye,pos));
	m[vX] = vec4_normalize(vec4_cross(up, m[vZ]));
	m[vY] = vec4_normalize(vec4_cross(m[vZ], m[vX]));
	m[vW] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	return m;
}
