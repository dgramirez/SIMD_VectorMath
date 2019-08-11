#include "mat_test.h"
#include "tMath.h"

//My conversion functions uses more accurate PI, PI/180 and 180/PI.
//So i end up creating Engine Math's version of these to get their results.
static const float PI = 3.14159f;
static const float PI_OVER_180 = PI / 180.0f;
static const float _180_OVER_PI = 180.0f / PI;

bool test_mat4_zero()
{
	mat4 t = mat4_zero();
	mat4 a;
	a[0] = _mm_set1_ps(0.0f);
	a[1] = _mm_set1_ps(0.0f);
	a[2] = _mm_set1_ps(0.0f);
	a[3] = _mm_set1_ps(0.0f);

	return mat4_isequal(t, a);
}
bool test_mat4_identity()
{
	mat4 t = mat4_identity();
	mat4 a;
	a[0] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	a[1] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	a[2] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	a[3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	return mat4_isequal(t, a);
}
bool test_mat4_translation()
{
	mat4 t = mat4_translation(-8, 1, 0);

	//Column Major Answer
	mat4 a;
	a[0] = _mm_set_ps(1.0f, 0.0f, 0.0f, -8.0f);
	a[1] = _mm_set_ps(0.0f, 1.0f, 0.0f,  1.0f);
	a[2] = _mm_set_ps(0.0f, 0.0f, 1.0f,  0.0f);
	a[3] = _mm_set_ps(0.0f, 0.0f, 0.0f,  1.0f);

	//FIX: The EngineMath's Translation is Column Major. Math Library is Row Major
	a = mat4_transpose(a);

	return mat4_isequal(t, a);
}
bool test_mat4_scale()
{
	mat4 test[2] = {};
	mat4 ans[2] = {};

	test[0] = mat4_scale(-7, 2, 4);
	ans[0][0] = _mm_set_ps(-7.0f, 0.0f, 0.0f, 0.0f);
	ans[0][1] = _mm_set_ps( 0.0f, 2.0f, 0.0f, 0.0f);
	ans[0][2] = _mm_set_ps( 0.0f, 0.0f, 4.0f, 0.0f);
	ans[0][3] = _mm_set_ps( 0.0f, 0.0f, 0.0f, 1.0f);
	
	test[1] = mat4_scale(4, 1, -2);
	ans[1][0] = _mm_set_ps(4.0f, 0.0f,  0.0f, 0.0f);
	ans[1][1] = _mm_set_ps(0.0f, 1.0f,  0.0f, 0.0f);
	ans[1][2] = _mm_set_ps(0.0f, 0.0f, -2.0f, 0.0f);
	ans[1][3] = _mm_set_ps(0.0f, 0.0f,  0.0f, 1.0f);

	return mat4_isequal(test[0], ans[0]) && mat4_isequal(test[1], ans[1]);
}
bool test_mat4_rotation_x()
{
	mat4 test[3] = {};
	mat4 ans[3] = {};

	test[0] = mat4_rotation_x(131.91319f * PI_OVER_180);
	ans[0][0] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	ans[0][1] = _mm_set_ps(0.0f, -0.66800249f, -0.74415904f, 0.0f);
	ans[0][2] = _mm_set_ps(0.0f,  0.74415904f, -0.66800249f, 0.0f);
	ans[0][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[1] = mat4_rotation_x(330.74631f * PI_OVER_180);
	ans[1][0] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	ans[1][1] = _mm_set_ps(0.0f, 0.87246221f, 0.48868158f, 0.0f);
	ans[1][2] = _mm_set_ps(0.0f, -0.48868158f, 0.87246221f, 0.0f);
	ans[1][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[2] = mat4_rotation_x(163.8922f * PI_OVER_180);
	ans[2][0] = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
	ans[2][1] = _mm_set_ps(0.0f, -0.96074069f, -0.27744788f, 0.0f);
	ans[2][2] = _mm_set_ps(0.0f,  0.27744788f, -0.96074069f, 0.0f);
	ans[2][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	return mat4_isequal(test[0], ans[0]) && mat4_isequal(test[1], ans[1]) && mat4_isequal(test[2], ans[2]);
}
bool test_mat4_rotation_y()
{
	mat4 test[3] = {};
	mat4 ans[3] = {};

	test[0] = mat4_rotation_y(33.015999f * PI_OVER_180);
	ans[0][0] = _mm_set_ps( 0.83851874f, 0.0f, 0.54487276f, 0.0f);
	ans[0][1] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	ans[0][2] = _mm_set_ps(-0.54487276f, 0.0f, 0.83851874f, 0.0f);
	ans[0][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[1] = mat4_rotation_y(164.4507f * PI_OVER_180);
	ans[1][0] = _mm_set_ps(-0.96339959f, 0.0f,  0.26806954f, 0.0f);
	ans[1][1] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	ans[1][2] = _mm_set_ps(-0.26806954f, 0.0f, -0.96339959f, 0.0f);
	ans[1][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[2] = mat4_rotation_y(249.0506f * PI_OVER_180);
	ans[2][0] = _mm_set_ps(-0.35754675f, 0.0f, -0.93389523f, 0.0f);
	ans[2][1] = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
	ans[2][2] = _mm_set_ps( 0.93389523f, 0.0f, -0.35754675f, 0.0f);
	ans[2][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	return mat4_isequal(test[0], ans[0]) && mat4_isequal(test[1], ans[1]) && mat4_isequal(test[2], ans[2]);
}
bool test_mat4_rotation_z()
{
	mat4 test[3] = {};
	mat4 ans[3] = {};

	test[0] = mat4_rotation_z(21.6563f * PI_OVER_180);
	ans[0][0] = _mm_set_ps(0.92941445f, -0.36903772f, 0.0f, 0.0f);
	ans[0][1] = _mm_set_ps(0.36903772f,  0.92941445f, 0.0f, 0.0f);
	ans[0][2] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	ans[0][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[1] = mat4_rotation_z(78.298203f * PI_OVER_180);
	ans[1][0] = _mm_set_ps(0.20281908f, -0.97921622f, 0.0f, 0.0f);
	ans[1][1] = _mm_set_ps(0.97921622f,  0.20281908f, 0.0f, 0.0f);
	ans[1][2] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	ans[1][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	test[2] = mat4_rotation_z(312.897f * PI_OVER_180);
	ans[2][0] = _mm_set_ps( 0.68067944f, 0.73258144f, 0.0f, 0.0f);
	ans[2][1] = _mm_set_ps(-0.73258144f, 0.68067944f, 0.0f, 0.0f);
	ans[2][2] = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
	ans[2][3] = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

	return mat4_isequal(test[0], ans[0]) && mat4_isequal(test[1], ans[1]) && mat4_isequal(test[2], ans[2]);
}
bool test_mat4_add()
{
	mat4 test[4] = {};
	mat4 ans[2] = {};

	test[0][0] = _mm_set_ps(-6, -5,  8, -6);
	test[0][1] = _mm_set_ps(-6, -5, -2,  6);
	test[0][2] = _mm_set_ps( 3, -3,  5,  4);
	test[0][3] = _mm_set_ps(-5, -5,  3, -4);
	test[1][0] = _mm_set_ps( 0,  3,  7,  5);
	test[1][1] = _mm_set_ps(-8,  7,  2, -7);
	test[1][2] = _mm_set_ps( 3, -8,  7, -7);
	test[1][3] = _mm_set_ps(-7, -5, -6,  2);
	ans[0][0] = _mm_set_ps( -6,  -2, 15, -1);
	ans[0][1] = _mm_set_ps(-14,   2,  0, -1);
	ans[0][2] = _mm_set_ps(  6, -11, 12, -3);
	ans[0][3] = _mm_set_ps(-12, -10, -3, -2);

	test[2][0] = _mm_set_ps( 6, -3,  0,  2);
	test[2][1] = _mm_set_ps(-4, -5, -6, -3);
	test[2][2] = _mm_set_ps(-3,  1, -6,  2);
	test[2][3] = _mm_set_ps(-2, -7, -9,  3);
	test[3][0] = _mm_set_ps(-4, -7, -5, -1);
	test[3][1] = _mm_set_ps( 0,  4, -8, -1);
	test[3][2] = _mm_set_ps(-6, -6,  6,  5);
	test[3][3] = _mm_set_ps( 1, -9, -6, -7);
	ans[1][0] = _mm_set_ps( 2, -10,  -5,  1);
	ans[1][1] = _mm_set_ps(-4,  -1, -14, -4);
	ans[1][2] = _mm_set_ps(-9,  -5,   0,  7);
	ans[1][3] = _mm_set_ps(-1, -16, -15, -4);

	mat4 t0 = mat4_add(test[0], test[1]);
	mat4 t1 = mat4_add(test[2], test[3]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]);
}
bool test_mat4_sub()
{
	mat4 test[4] = {};
	mat4 ans[2] = {};

	test[0][0] = _mm_set_ps( 5, -5, -6,  0);
	test[0][1] = _mm_set_ps(-4, -3, -8, -9);
	test[0][2] = _mm_set_ps(-6,  5,  4, -2);
	test[0][3] = _mm_set_ps( 2,  3,  4,  5);
	test[1][0] = _mm_set_ps(-7, -7,  7, -9);
	test[1][1] = _mm_set_ps(-7,  7,  4,  4);
	test[1][2] = _mm_set_ps( 8,  8, -2,  8);
	test[1][3] = _mm_set_ps( 7, -4,  1,  3);
	ans[0][0] = _mm_set_ps( 12,   2, -13,   9);
	ans[0][1] = _mm_set_ps(  3, -10, -12, -13);
	ans[0][2] = _mm_set_ps(-14,  -3,   6, -10);
	ans[0][3] = _mm_set_ps( -5,   7,   3,   2);

	test[2][0] = _mm_set_ps(-3,  7, -8,  5);
	test[2][1] = _mm_set_ps( 4, -9,  8, -6);
	test[2][2] = _mm_set_ps( 2, -7, -3,  0);
	test[2][3] = _mm_set_ps( 2,  8,  5, -6);
	test[3][0] = _mm_set_ps( 2, -8,  7,  8);
	test[3][1] = _mm_set_ps(-9,  0,  2, -6);
	test[3][2] = _mm_set_ps(-6,  0,  8, -6);
	test[3][3] = _mm_set_ps( 3, -2,  4, -9);
	ans[1][0] = _mm_set_ps(-5, 15, -15, -3);
	ans[1][1] = _mm_set_ps(13, -9,   6,  0);
	ans[1][2] = _mm_set_ps( 8, -7, -11,  6);
	ans[1][3] = _mm_set_ps(-1, 10,   1,  3);

	mat4 t0 = mat4_sub(test[0], test[1]);
	mat4 t1 = mat4_sub(test[2], test[3]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]);
}
bool test_mat4_mul_scalar()
{
	mat4 test[2] = {};
	float scalar[2] = {};
	mat4 ans[2] = {};

	scalar[0] = 4.0f;
	test[0][0] = _mm_set_ps(-2.0f, -6.0f,  8.0f, -2.0f);
	test[0][1] = _mm_set_ps(-5.0f, -9.0f, -9.0f,  2.0f);
	test[0][2] = _mm_set_ps(-1.0f,  0.0f,  3.0f,  2.0f);
	test[0][3] = _mm_set_ps(-9.0f, -2.0f, -5.0f,  6.0f);
	ans[0][0] = _mm_set_ps( -8.0f, -24.0f,  32.0f,  -8.0f);
	ans[0][1] = _mm_set_ps(-20.0f, -36.0f, -36.0f,   8.0f);
	ans[0][2] = _mm_set_ps( -4.0f,   0.0f,  12.0f,   8.0f);
	ans[0][3] = _mm_set_ps(-36.0f,  -8.0f, -20.0f,  24.0f);

	scalar[1] = 3.0f;
	test[1][0] = _mm_set_ps(-5.0f,  5.0f,  2.0f, -6.0f);
	test[1][1] = _mm_set_ps( 5.0f,  8.0f, -5.0f, -4.0f);
	test[1][2] = _mm_set_ps( 0.0f, -4.0f,  8.0f,  1.0f);
	test[1][3] = _mm_set_ps( 5.0f, -2.0f,  1.0f, -6.0f);
	ans[1][0] = _mm_set_ps(-15.0f,  15.0f,   6.0f, -18.0f);
	ans[1][1] = _mm_set_ps( 15.0f,  24.0f, -15.0f, -12.0f);
	ans[1][2] = _mm_set_ps(  0.0f, -12.0f,  24.0f,   3.0f);
	ans[1][3] = _mm_set_ps( 15.0f,  -6.0f,   3.0f, -18.0f);

	mat4 t0 = mat4_mul(test[0], scalar[0]);
	mat4 t1 = mat4_mul(test[1], scalar[1]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]);
}
bool test_mat4_negate()
{
	mat4 test[2] = {};
	mat4 ans[2] = {};

	test[0][0] = _mm_set_ps(-3.0f, -5.0f, -6.0f, -5.0f);
	test[0][1] = _mm_set_ps( 2.0f,  5.0f,  5.0f,  0.0f);
	test[0][2] = _mm_set_ps( 7.0f, -5.0f, -3.0f,  4.0f);
	test[0][3] = _mm_set_ps(-5.0f, -2.0f,  8.0f,  2.0f);
	ans[0][0] = _mm_set_ps( 3.0f,  5.0f,  6.0f,  5.0f);
	ans[0][1] = _mm_set_ps(-2.0f, -5.0f, -5.0f, -0.0f);
	ans[0][2] = _mm_set_ps(-7.0f,  5.0f,  3.0f, -4.0f);
	ans[0][3] = _mm_set_ps( 5.0f,  2.0f, -8.0f, -2.0f);

	test[1][0] = _mm_set_ps( 7.0f,  0.0f, -2.0f, -1.0f);
	test[1][1] = _mm_set_ps(-7.0f, -8.0f, -5.0f,  2.0f);
	test[1][2] = _mm_set_ps(-9.0f,  8.0f,  8.0f, -2.0f);
	test[1][3] = _mm_set_ps(-3.0f, -6.0f, -5.0f,  5.0f);
	ans[1][0] = _mm_set_ps(-7.0f, -0.0f,  2.0f,  1.0f);
	ans[1][1] = _mm_set_ps( 7.0f,  8.0f,  5.0f, -2.0f);
	ans[1][2] = _mm_set_ps( 9.0f, -8.0f, -8.0f,  2.0f);
	ans[1][3] = _mm_set_ps( 3.0f,  6.0f,  5.0f, -5.0f);

	mat4 t0 = mat4_negate(test[0]);
	mat4 t1 = mat4_negate(test[1]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]);
}
bool test_mat4_transpose()
{
		mat4 test[2] = {};
	mat4 ans[2] = {};

	test[0][0] = _mm_set_ps(-4.0f, -5.0f,  7.0f, -9.0f);
	test[0][1] = _mm_set_ps(-6.0f, -1.0f, -3.0f,  3.0f);
	test[0][2] = _mm_set_ps( 7.0f,  7.0f, -8.0f,  5.0f);
	test[0][3] = _mm_set_ps(-5.0f, -8.0f, -8.0f,  8.0f);
	ans[0][0] = _mm_set_ps(-4.0f, -6.0f,  7.0f, -5.0f);
	ans[0][1] = _mm_set_ps(-5.0f, -1.0f,  7.0f, -8.0f);
	ans[0][2] = _mm_set_ps( 7.0f, -3.0f, -8.0f, -8.0f);
	ans[0][3] = _mm_set_ps(-9.0f,  3.0f,  5.0f,  8.0f);

	test[1][0] = _mm_set_ps(-8.0f, -7.0f,  1.0f, -2.0f);
	test[1][1] = _mm_set_ps( 2.0f, -2.0f, -4.0f, -8.0f);
	test[1][2] = _mm_set_ps(-3.0f,  4.0f, -5.0f, -5.0f);
	test[1][3] = _mm_set_ps(-1.0f, -5.0f, 2.0f,  3.0f);
	ans[1][0] = _mm_set_ps(-8.0f,  2.0f, -3.0f, -1.0f);
	ans[1][1] = _mm_set_ps(-7.0f, -2.0f,  4.0f, -5.0f);
	ans[1][2] = _mm_set_ps( 1.0f, -4.0f, -5.0f,  2.0f);
	ans[1][3] = _mm_set_ps(-2.0f, -8.0f, -5.0f,  3.0f);

	mat4 t0 = mat4_transpose(test[0]);
	mat4 t1 = mat4_transpose(test[1]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]);
}
bool test_vec4_mul_vm()
{
	mat4 test[2] = {};
	vec4 v[2] = {};
	vec4 ans[2] = {};

	v[0] = _mm_set_ps(8.0f, -5.0f, 6.0f, 1.0f);
	test[0][0] = _mm_set_ps(-3.0f, 6.0f, -4.0f, 0.0f);
	test[0][1] = _mm_set_ps(2.0f, 1.0f, -6.0f, -7.0f);
	test[0][2] = _mm_set_ps(3.0f, 1.0f, 7.0f, 2.0f);
	test[0][3] = _mm_set_ps(6.0f, -3.0f, 3.0f, -1.0f);
	ans[0] = _mm_set_ps(-10.0f, 46.0f, 43.0f, 46.0f);

	v[1] = _mm_set_ps(7.0f, -8.0f, 2.0f, -4.0f);
	test[1][0] = _mm_set_ps(-6.0f, 5.0f, -2.0f, -3.0f);
	test[1][1] = _mm_set_ps(-2.0f, 2.0f, 7.0f, -4.0f);
	test[1][2] = _mm_set_ps(-7.0f, -5.0f, -4.0f, 2.0f);
	test[1][3] = _mm_set_ps(-9.0f, 6.0f, -7.0f, -5.0f);
	ans[1] = _mm_set_ps(-4.0f, -15.0f, -50.0f, 35.0f);

	vec4 t0 = vec4_mul(v[0], test[0]);
	vec4 t1 = vec4_mul(v[1], test[1]);

	return vec4_isequal(t0, ans[0]) && vec4_isequal(t1, ans[1]);
}
bool test_vec4_mul_mv()
{
	mat4 test[2] = {};
	vec4 v[2] = {};
	vec4 ans[2] = {};


	test[0][0] = _mm_set_ps(0.0f, -1.0f, 1.0f, 6.0f);
	test[0][1] = _mm_set_ps(-4.0f, -7.0f, -9.0f, -5.0f);
	test[0][2] = _mm_set_ps(-6.0f, -3.0f, 0.0f, 7.0f);
	test[0][3] = _mm_set_ps(4.0f, -1.0f, -4.0f, 5.0f);
	v[0] = _mm_set_ps(7.0f, 8.0f, -4.0f, 5.0f);
	ans[0] = _mm_set_ps(18.0f, -73.0f, -31.0f, 61.0f);

	test[1][0] = _mm_set_ps(-6.0f, -4.0f, -7.0f, -7.0f);
	test[1][1] = _mm_set_ps(-8.0f, 8.0f, 4.0f, 3.0f);
	test[1][2] = _mm_set_ps(7.0f, 4.0f, 5.0f, -5.0f);
	test[1][3] = _mm_set_ps(-1.0f, 8.0f, -2.0f, 1.0f);
	v[1] = _mm_set_ps(4.0f, 3.0f, -5.0f, -6.0f);
	ans[1] = _mm_set_ps(41.0f, -46.0f, 45.0f, 24.0f);

	vec4 t0 = vec4_mul(test[0], v[0]);
	vec4 t1 = vec4_mul(test[1], v[1]);

	return vec4_isequal(t0, ans[0]) && vec4_isequal(t1, ans[1]);
}
bool test_mat4_mul()
{
	mat4 test[6] = {};
	mat4 ans[3] = {};

	test[0][0] = _mm_set_ps(-6.0f,  0.0f,  4.0f, -8.0f);
	test[0][1] = _mm_set_ps(-9.0f, -2.0f, -7.0f, -5.0f);
	test[0][2] = _mm_set_ps( 3.0f,  1.0f, -7.0f, -1.0f);
	test[0][3] = _mm_set_ps( 7.0f, -4.0f, -5.0f, -3.0f);
	test[1][0] = _mm_set_ps(-3.0f, -9.0f,  1.0f,  0.0f);
	test[1][1] = _mm_set_ps(-2.0f,  8.0f, -7.0f, -6.0f);
	test[1][2] = _mm_set_ps(-7.0f, -7.0f,  7.0f, -8.0f);
	test[1][3] = _mm_set_ps( 3.0f,  6.0f, -5.0f,  6.0f);
	ans[0][0] = _mm_set_ps(-34.0f, -22.0f,  62.0f, -80.0f);
	ans[0][1] = _mm_set_ps( 65.0f,  84.0f, -19.0f,  38.0f);
	ans[0][2] = _mm_set_ps( 35.0f,  24.0f, -48.0f,  44.0f);
	ans[0][3] = _mm_set_ps( 13.0f, -78.0f,  15.0f,  46.0f);

	test[2][0] = _mm_set_ps(-8.0f,  0.0f, -2.0f,  4.0f);
	test[2][1] = _mm_set_ps(-1.0f,  1.0f,  4.0f, -1.0f);
	test[2][2] = _mm_set_ps( 1.0f, -2.0f, -8.0f,  8.0f);
	test[2][3] = _mm_set_ps(-1.0f,  8.0f, -2.0f,  2.0f);
	test[3][0] = _mm_set_ps(-2.0f,  5.0f,  4.0f,  3.0f);
	test[3][1] = _mm_set_ps(-9.0f, -5.0f,  2.0f, -5.0f);
	test[3][2] = _mm_set_ps(-7.0f,  1.0f,  1.0f, -2.0f);
	test[3][3] = _mm_set_ps( 0.0f,  2.0f, -2.0f, -9.0f);
	ans[1][0] = _mm_set_ps( 30.0f, -34.0f, -42.0f, -56.0f);
	ans[1][1] = _mm_set_ps(-35.0f,  -8.0f,   4.0f,  -7.0f);
	ans[1][2] = _mm_set_ps( 72.0f,  23.0f, -24.0f, -43.0f);
	ans[1][3] = _mm_set_ps(-56.0f, -43.0f,   6.0f, -57.0f);

	test[4][0] = _mm_set_ps(-1.0f, -8.0f, -1.0f, -1.0f);
	test[4][1] = _mm_set_ps(-5.0f, -2.0f, -8.0f,  1.0f);
	test[4][2] = _mm_set_ps( 7.0f,  2.0f, -2.0f, -2.0f);
	test[4][3] = _mm_set_ps(-3.0f, -8.0f, -7.0f, -5.0f);
	test[5][0] = _mm_set_ps(-3.0f, -4.0f,  3.0f,  8.0f);
	test[5][1] = _mm_set_ps( 1.0f,  0.0f, -3.0f,  1.0f);
	test[5][2] = _mm_set_ps(-9.0f, -1.0f, -4.0f, -7.0f);
	test[5][3] = _mm_set_ps( 5.0f, -2.0f,  8.0f, -6.0f);
	ans[2][0] = _mm_set_ps( -1.0f,   7.0f, 17.0f, -3.0f);
	ans[2][1] = _mm_set_ps( 90.0f,  26.0f, 31.0f,  8.0f);
	ans[2][2] = _mm_set_ps(-11.0f, -22.0f,  7.0f, 84.0f);
	ans[2][3] = _mm_set_ps( 39.0f,  29.0f,  3.0f, 47.0f);

	mat4 t0 = mat4_mul(test[0], test[1]);
	mat4 t1 = mat4_mul(test[2], test[3]);
	mat4 t2 = mat4_mul(test[4], test[5]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]) && mat4_isequal(t2, ans[2]);
}
bool test_mat4_determinant()
{
	mat4 test[4] = {};
	float ans[4] = {};

	test[0][0] = _mm_set_ps(-4.0f,  8.0f, -7.0f,  4.0f);
	test[0][1] = _mm_set_ps( 7.0f,  4.0f,  5.0f,  0.0f);
	test[0][2] = _mm_set_ps( 6.0f, -8.0f, -9.0f,  2.0f);
	test[0][3] = _mm_set_ps(-3.0f, -5.0f,  7.0f, -9.0f);
	ans[0] = -6318.0f;

	test[1][0] = _mm_set_ps( 6.0f,  3.0f, -8.0f, -1.0f);
	test[1][1] = _mm_set_ps( 2.0f, -1.0f,  6.0f, -7.0f);
	test[1][2] = _mm_set_ps(-6.0f,  1.0f,  3.0f, -4.0f);
	test[1][3] = _mm_set_ps(-9.0f, -6.0f,  1.0f,  3.0f);
	ans[1] = 2888.0f;

	test[2][0] = _mm_set_ps(-9.0f,  6.0f,  0.0f,  0.0f);
	test[2][1] = _mm_set_ps(-9.0f,  8.0f, -7.0f, -5.0f);
	test[2][2] = _mm_set_ps(-5.0f,  0.0f,  2.0f,  3.0f);
	test[2][3] = _mm_set_ps( 1.0f,  2.0f,  1.0f,  2.0f);
	ans[2] = 516.0f;

	test[3][0] = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	test[3][1] = _mm_set_ps(2.0f, 3.0f, 4.0f, 5.0f);
	test[3][2] = _mm_set_ps(3.0f, 4.0f, 5.0f, 6.0f);
	test[3][3] = _mm_set_ps(4.0f, 5.0f, 6.0f, 7.0f);
	ans[3] = 0.0f;

	vec4 t0 = _mm_set1_ps(mat4_determinant(test[0]));
	vec4 t1 = _mm_set1_ps(mat4_determinant(test[1]));
	vec4 t2 = _mm_set1_ps(mat4_determinant(test[2]));
	vec4 t3 = _mm_set1_ps(mat4_determinant(test[3]));
	
	return vec4_isequal(t0, _mm_set1_ps(ans[0])) && vec4_isequal(t1, _mm_set1_ps(ans[1])) && vec4_isequal(t2, _mm_set1_ps(ans[2])) && vec4_isequal(t3, _mm_set1_ps(ans[3]));
}
bool test_mat4_inverse()
{
	mat4 test[4] = {};
	mat4 ans[4] = {};

	test[0][0] = _mm_set_ps(-4.0f, -6.0f, -1.0f,  4.0f);
	test[0][1] = _mm_set_ps( 8.0f, -8.0f,  6.0f,  1.0f);
	test[0][2] = _mm_set_ps( 6.0f,  4.0f,  1.0f, -9.0f);
	test[0][3] = _mm_set_ps( 5.0f, -5.0f, -4.0f, -1.0f);
	ans[0][0] = _mm_set_ps(-0.18921569f,  0.042156864f, -0.089215688f,   0.088235296f);
	ans[0][1] = _mm_set_ps(-0.18267974f, -0.023202615f, -0.082679741f, -0.0098039219f);
	ans[0][2] = _mm_set_ps(0.042483661f,  0.075163402f,  0.042483661f,   -0.13725491f);
	ans[0][3] = _mm_set_ps(-0.20261438f,  0.026143791f,  -0.20261438f,   0.039215688f);

	test[1][0] = _mm_set_ps( 5.0f, -1.0f,  3.0f,  7.0f);
	test[1][1] = _mm_set_ps(-3.0f,  7.0f,  2.0f, -5.0f);
	test[1][2] = _mm_set_ps( 0.0f,  7.0f,  5.0f,  7.0f);
	test[1][3] = _mm_set_ps(-5.0f,  6.0f, -2.0f,  0.0f);
	ans[1][0] = _mm_set_ps(  0.5726496f,   0.27920228f, -0.37321937f,  0.20512821f);
	ans[1][1] = _mm_set_ps( 0.33760685f,    0.1994302f, -0.19515669f,  0.21794872f);
	ans[1][2] = _mm_set_ps(-0.41880342f, -0.099715099f,  0.34757835f, -0.35897437f);
	ans[1][3] = _mm_set_ps(-0.03846154f,  -0.12820512f, 0.089743592f,  0.03846154f);

	test[2][0] = _mm_set_ps( 2.0f, -8.0f, -3.0f,  1.0f);
	test[2][1] = _mm_set_ps(-4.0f, -7.0f,  3.0f, -1.0f);
	test[2][2] = _mm_set_ps( 3.0f,  8.0f, -2.0f,  7.0f);
	test[2][3] = _mm_set_ps( 6.0f,  1.0f,  2.0f, -3.0f);
	ans[2][0] = _mm_set_ps( 0.058403924f, 0.0049041463f,   0.046812307f,   0.12706198f);
	ans[2][1] = _mm_set_ps(-0.074453861f, -0.067320555f, -0.0062416405f, -0.016941596f);
	ans[2][2] = _mm_set_ps( -0.08381632f,   0.22960322f,    0.10075791f,   0.13062863f);
	ans[2][3] = _mm_set_ps( 0.036112349f,   0.14043692f,    0.15871601f, 0.0022291574f);

	test[3][0] = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	test[3][1] = _mm_set_ps(2.0f, 3.0f, 4.0f, 5.0f);
	test[3][2] = _mm_set_ps(3.0f, 4.0f, 5.0f, 6.0f);
	test[3][3] = _mm_set_ps(4.0f, 5.0f, 6.0f, 7.0f);
	ans[3][0] = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	ans[3][1] = _mm_set_ps(2.0f, 3.0f, 4.0f, 5.0f);
	ans[3][2] = _mm_set_ps(3.0f, 4.0f, 5.0f, 6.0f);
	ans[3][3] = _mm_set_ps(4.0f, 5.0f, 6.0f, 7.0f);

	mat4 t0 = mat4_inverse(test[0]);
	mat4 t1 = mat4_inverse(test[1]);
	mat4 t2 = mat4_inverse(test[2]);
	mat4 t3 = mat4_inverse(test[3]);

	return mat4_isequal(t0, ans[0]) && mat4_isequal(t1, ans[1]) && mat4_isequal(t2, ans[2]) && mat4_isequal(t3, ans[3]);
}
