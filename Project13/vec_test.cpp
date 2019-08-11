#include "vec_test.h"
#include "tMath.h"

bool test_vec4_isequal()
{
	vec4 test[6];
	test[0] = _mm_set_ps(-2, 0, -4, 1);
	test[1] = _mm_set_ps(-2, 0, -4, 1);

	test[2] = _mm_set_ps(-2, 0, -4, 1);
	test[3] = _mm_set_ps(-2, 1.9999999e-05f, -4, 1);

	test[4] = _mm_set_ps(-2, 0, -4, 1);
	test[5] = _mm_set_ps(-2, 0, -4, 1.000005f);

	bool t1 = vec4_isequal(test[0], test[1]);
	bool t2 = vec4_isequal(test[2], test[3]);
	bool t3 = vec4_isequal(test[4], test[5]); //FAIL: EPSILON < 0.00001f.

	return t1 & !t2 & t3;
}
bool test_vec4_add()
{
	vec4 test[4];
	vec4 ans[2];

	test[0] = _mm_set_ps(1, -2, -9, 1);
	test[1] = _mm_set_ps(-9, -8, -6, -8);
	ans[0] = _mm_set_ps(-8, -10, -15, -7);

	test[2] = _mm_set_ps(6, -2, 7, 0);
	test[3] = _mm_set_ps(8, 1, -2, 0);
	ans[1] = _mm_set_ps(14, -1, 5, 0);

	vec4 t1 = vec4_add(test[0], test[1]);
	vec4 t2 = vec4_add(test[2], test[3]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_sub()
{
	vec4 test[4];
	vec4 ans[2];

	test[0] = _mm_set_ps(6, 7, 7, -6);
	test[1] = _mm_set_ps(-3, -8, -2, -3);
	ans[0] = _mm_set_ps(9, 15, 9, -3);

	test[2] = _mm_set_ps(-6, -9, 4, 0);
	test[3] = _mm_set_ps(-8, -2, 7, 0);
	ans[1] = _mm_set_ps(2, -7, -3, 0);

	vec4 t1 = vec4_sub(test[0], test[1]);
	vec4 t2 = vec4_sub(test[2], test[3]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_mul_scalar()
{
	vec4 test[3];
	float scalar[3];
	vec4 ans[3];

	test[0] = _mm_set_ps(-9, 3, 4, 5);
	scalar[0] = -4;
	ans[0] = _mm_set_ps(36, -12, -16, -20);

	test[1] = _mm_set_ps(-4, -2, -4, 8);
	scalar[1] = 2;
	ans[1] = _mm_set_ps(-8, -4, -8, 16);

	test[2] = _mm_set_ps(-4, 1, -6, 7);
	scalar[2] = 8;
	ans[2] = _mm_set_ps(-32, 8, -48, 56);

	vec4 t1 = vec4_mul(test[0], scalar[0]);
	vec4 t2 = vec4_mul(test[1], scalar[1]);
	vec4 t3 = vec4_mul(test[2], scalar[2]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]);
}
bool test_vec4_negate()
{
	vec4 test[2];
	vec4 ans[2];

	test[0] = _mm_set_ps(8, 5, -6, -5);
	ans[0] = _mm_set_ps(-8, -5, 6, 5);

	test[1] = _mm_set_ps(5, 3, -3, 5);
	ans[1] = _mm_set_ps(-5, -3, 3, -5);


	vec4 t1 = vec4_negate(test[0]);
	vec4 t2 = vec4_negate(test[1]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_dot()
{
	vec4 test[4];
	float ans[2];

	test[0] = _mm_set_ps(-7, -2, 1, -2);
	test[1] = _mm_set_ps(-4, 2, 7, 5);
	ans[0] = 21;

	test[2] = _mm_set_ps(0, -1, 6, -7);
	test[3] = _mm_set_ps(-7, 8, 3, -2);
	ans[1] = 24;

	float t1 = vec4_dot(test[0], test[1]);
	float t2 = vec4_dot(test[2], test[3]);

	return t1 == ans[0] && t2 == ans[1];
}
bool test_vec4_cross()
{
	vec4 test[4];
	vec4 ans[2];

	test[0] = _mm_set_ps(-2, 5, 4, 0);
	test[1] = _mm_set_ps(-6, 8, 2, 0);
	ans[0] = _mm_set_ps(-22, -20, 14, 0);

	test[2] = _mm_set_ps(6, 6, 8, -9);
	test[3] = _mm_set_ps(-2, 7, 6, -3);
	ans[1] = _mm_set_ps(-20, -52, 54, 0);

	vec4 t1 = vec4_cross(test[0], test[1]);
	vec4 t2 = vec4_cross(test[2], test[3]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_length2()
{
	vec4 test[2];
	float ans[2];

	test[0] = _mm_set_ps(-6, 2, -2, 0);
	ans[0] = 44;

	test[1] = _mm_set_ps(-1, -1, -5, 8);
	ans[1] = 91;


	float t1 = vec4_length2(test[0]);
	float t2 = vec4_length2(test[1]);

	return t1 == ans[0] && t2 == ans[1];
}
bool test_vec4_length()
{
	vec4 test[2];
	float ans[2];

	test[0] = _mm_set_ps(4, -5, 1, -9);
	ans[0] = 11.090536f;

	test[1] = _mm_set_ps(-8, -1, -9, -5);
	ans[1] = 13.076696f;


	float t1 = vec4_length(test[0]);
	float t2 = vec4_length(test[1]);

	return t1 == ans[0] && t2 == ans[1];
}
bool test_vec4_normalize()
{
	vec4 test[3];
	vec4 ans[3];

	test[0] = _mm_set_ps(-9, 1, 0, 5);
	ans[0] = _mm_set_ps(-0.87006289f, 0.096673653f, 0, 0.48336828f);

	test[1] = _mm_set_ps(-4, -7, -1, 2);
	ans[1] = _mm_set_ps(-0.47809145f, -0.83666003f, -0.11952286f, 0.23904572f);

	test[2] = _mm_set_ps(0, 0, 0, 0);
	ans[2] = _mm_set_ps(0, 0, 0, 0);

	vec4 t1 = vec4_normalize(test[0]);
	vec4 t2 = vec4_normalize(test[1]);
	vec4 t3 = vec4_normalize(test[2]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]);
}
bool test_vec4_homogenize()
{
	vec4 test[2];
	vec4 ans[2];

	test[0] = _mm_set_ps(-5, -1, 3, -3);
	ans[0] = _mm_set_ps(1.6666666f, 0.33333334f, -1, 1);

	test[1] = _mm_set_ps(0, 0, 0, 0);
	ans[1] = _mm_set_ps(0, 0, 0, 0);

	vec4 t1 = vec4_homogenize(test[0]);
	vec4 t2 = vec4_homogenize(test[1]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_max()
{
	vec4 test[4];
	vec4 ans[2];

	test[0] = _mm_set_ps(-4, 5, -2, -9);
	test[1] = _mm_set_ps(-4, 2, -4, 0);
	ans[0] = _mm_set_ps(-4, 5, -2, 0);

	test[2] = _mm_set_ps(3, 8, -2, -2);
	test[3] = _mm_set_ps(-6, 7, -3, 1);
	ans[1] = _mm_set_ps(3, 8, -2, 1);

	vec4 t1 = vec4_max(test[0], test[1]);
	vec4 t2 = vec4_max(test[2], test[3]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_min()
{
	vec4 test[4];
	vec4 ans[2];

	test[0] = _mm_set_ps(1, 7, 7, -6);
	test[1] = _mm_set_ps(-7, 8, 0, -5);
	ans[0] = _mm_set_ps(-7, 7, 0, -6);

	test[2] = _mm_set_ps(-9, 1, 5, 5);
	test[3] = _mm_set_ps(4, -2, 0, 3);
	ans[1] = _mm_set_ps(-9, -2, 0, 3);

	vec4 t1 = vec4_min(test[0], test[1]);
	vec4 t2 = vec4_min(test[2], test[3]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]);
}
bool test_vec4_avg()
{
	vec4 test[6];
	vec4 ans[3];

	test[0] = _mm_set_ps(-4, 5, 3, 2);
	test[1] = _mm_set_ps(-9, 8, -1, -8);
	ans[0] = _mm_set_ps(-6.5, 6.5, 1, -3);

	test[2] = _mm_set_ps(-1, -1, -6, 0);
	test[3] = _mm_set_ps(-6, 6, -8, 0);
	ans[1] = _mm_set_ps(-3.5, 2.5, -7, 0);

	test[4] = _mm_set_ps(-6, 3, 8, 0);
	test[5] = _mm_set_ps(0, 1, -9, 0);
	ans[2] = _mm_set_ps(-3, 2, -0.5, 0);

	vec4 t1 = vec4_avg(test[0], test[1]);
	vec4 t2 = vec4_avg(test[2], test[3]);
	vec4 t3 = vec4_avg(test[4], test[5]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]);
}
bool test_vec4_anglebetween()
{
	const float PI = 3.14159f;
	const float _180_OVER_PI = 180.0f / PI;

	vec4 test[14];
	vec4 ans[7];

	test[0] = _mm_set_ps(5, 2, -3, 0);
	test[1] = _mm_set_ps(8, 8, 1, 0);
	ans[0] = _mm_set1_ps(40.800613f);

	test[2] = _mm_set_ps(0, 0, 0, 0);
	test[3] = _mm_set_ps(8, -4, -7, 0);
	ans[1] = _mm_set1_ps(0);

	test[4] = _mm_set_ps(-3, -3, -8, 0);
	test[5] = _mm_set_ps(0, 0, 0, 0);
	ans[2] = _mm_set1_ps(0);

	test[6] = _mm_set_ps(0, 0, 0, 0);
	test[7] = _mm_set_ps(0, 0, 0, 0);
	ans[3] = _mm_set1_ps(0);

	test[8] = _mm_set_ps(2, -8, -5, -3);
	test[9] = _mm_set_ps(4, 4, 3, 1);
	ans[4] = _mm_set1_ps(129.91798f);

	test[10] = _mm_set_ps(0, 0, 0, 0);
	test[11] = _mm_set_ps(-6, -6, 5, -7);
	ans[5] = _mm_set1_ps(0);

	test[12] = _mm_set_ps(-8, 4, 7, -2);
	test[13] = _mm_set_ps(0, 0, 0, 0);
	ans[6] = _mm_set1_ps(0);

	vec4 t1 = _mm_set1_ps(vec4_anglebetween(test[0], test[1]) * _180_OVER_PI);
	vec4 t2 = _mm_set1_ps(vec4_anglebetween(test[2], test[3]) * _180_OVER_PI);
	vec4 t3 = _mm_set1_ps(vec4_anglebetween(test[4], test[5]) * _180_OVER_PI);
	vec4 t4 = _mm_set1_ps(vec4_anglebetween(test[6], test[7]) * _180_OVER_PI);
	vec4 t5 = _mm_set1_ps(vec4_anglebetween(test[8], test[9]) * _180_OVER_PI);
	vec4 t6 = _mm_set1_ps(vec4_anglebetween(test[10], test[11]) * _180_OVER_PI);
	vec4 t7 = _mm_set1_ps(vec4_anglebetween(test[12], test[13]) * _180_OVER_PI);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]) && vec4_isequal(t4, ans[3]) && vec4_isequal(t5, ans[4]) && vec4_isequal(t6, ans[5]) && vec4_isequal(t7, ans[6]);
}
bool test_vec4_component()
{
	vec4 test[8];
	float ans[4];

	test[0] = _mm_set_ps(-5, 8, 6, 0);
	test[1] = _mm_set_ps(-3, 2, -6, 0);
	ans[0] = -0.71428537f;

	test[2] = _mm_set_ps(6, 4, 4, 0);
	test[3] = _mm_set_ps(0, 0, 0, 0);
	ans[1] = 0;

	test[4] = _mm_set_ps(8, 3, -6, -4);
	test[5] = _mm_set_ps(0, 2, 6, -1);
	ans[2] = -4.0605173f;

	test[6] = _mm_set_ps(3, 3, -2, -8);
	test[7] = _mm_set_ps(0, 0, 0, 0);
	ans[3] = 0;

	float t1 = vec4_component(test[0], test[1]);
	float t2 = vec4_component(test[2], test[3]);
	float t3 = vec4_component(test[4], test[5]);
	float t4 = vec4_component(test[6], test[7]);

	return (t1 == ans[0]) && (t2 == ans[1]) && (t3 == ans[2]) && (t4 == ans[3]);
}
bool test_vec4_project()
{
	vec4 test[8];
	vec4 ans[4];

	test[0] = _mm_set_ps(7, 6, 6, 0);
	test[1] = _mm_set_ps(2, 3, 3, 0);
	ans[0] = _mm_set_ps(4.5454545f, 6.8181815f, 6.8181815f, 0);

	test[2] = _mm_set_ps(-4, 0, 6, 0);
	test[3] = _mm_set_ps(0, 0, 0, 0);
	ans[1] = _mm_set_ps(0, 0, 0, 0);

	test[4] = _mm_set_ps(-9, -8, 0, 5);
	test[5] = _mm_set_ps(0, 7, -9, -1);
	ans[2] = _mm_set_ps(-0, -3.2595417f, 4.1908393f, 0.46564883f);

	test[6] = _mm_set_ps(-2, -5, 3, 7);
	test[7] = _mm_set_ps(0, 0, 0, 0);
	ans[3] = _mm_set_ps(0, 0, 0, 0);

	vec4 t1 = vec4_project(test[0], test[1]);
	vec4 t2 = vec4_project(test[2], test[3]);
	vec4 t3 = vec4_project(test[4], test[5]);
	vec4 t4 = vec4_project(test[6], test[7]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]) && vec4_isequal(t4, ans[3]);
}
bool test_vec4_reflect()
{
	vec4 test[10];
	vec4 ans[5];

	test[0] = _mm_set_ps(2, 2, 5, 0);
	test[1] = _mm_set_ps(7, -7, -3, 0);
	ans[0] = _mm_set_ps(-3.9626169f, -0.03738296f, -4.1588783f, -0);

	test[2] = _mm_set_ps(3, -8, 0, 0);
	test[3] = _mm_set_ps(0, 0, 0, 0);
	ans[1] = _mm_set_ps(-3, 8, -0, -0);

	test[4] = _mm_set_ps(-1, 4, -7, -8);
	test[5] = _mm_set_ps(5, 2, -7, -1);
	ans[2] = _mm_set_ps(8.5949373f, -0.96202517f, -3.6329117f, 6.4810123f);

	test[6] = _mm_set_ps(-4, -4, 7, 6);
	test[7] = _mm_set_ps(0, 0, 0, 0);
	ans[3] = _mm_set_ps(4, 4, -7, -6);

	test[8] = _mm_set_ps(-5, -2, -7, 0);
	test[9] = _mm_set_ps(1, 0, 0, 0);
	ans[4] = _mm_set_ps(-5, 2, 7, -0);

	vec4 t1 = vec4_reflect(test[0], test[1]);
	vec4 t2 = vec4_reflect(test[2], test[3]);
	vec4 t3 = vec4_reflect(test[4], test[5]);
	vec4 t4 = vec4_reflect(test[6], test[7]);
	vec4 t5 = vec4_reflect(test[8], test[9]);

	return vec4_isequal(t1, ans[0]) && vec4_isequal(t2, ans[1]) && vec4_isequal(t3, ans[2]) && vec4_isequal(t4, ans[3]) && vec4_isequal(t5, ans[4]);
}
