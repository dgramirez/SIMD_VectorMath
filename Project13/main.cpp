#include <iostream>
#include "tMath.h"
#include "vec_test.h"
#include "mat_test.h"
#define LOG(x) std::cout << x << std::endl;

int main()
{
	#pragma region vec4_tests

	LOG("vec4_isequal: " << test_vec4_isequal());
	LOG("vec4_add: " << test_vec4_add());
	LOG("vec4_sub: " << test_vec4_sub());
	LOG("vec4_mul: " << test_vec4_mul_scalar());
	LOG("vec4_negate: " << test_vec4_negate());
	LOG("vec4_dot: " << test_vec4_dot());
	LOG("vec4_cross: " << test_vec4_cross());
	LOG("vec4_legnth2: " << test_vec4_length2());
	LOG("vec4_legnth: " << test_vec4_length());
	LOG("vec4_normalize: " << test_vec4_normalize());
	LOG("vec4_homogenize: " << test_vec4_homogenize());
	LOG("vec4_max: " << test_vec4_max());
	LOG("vec4_min: " << test_vec4_min());
	LOG("vec4_avg: " << test_vec4_avg());
	LOG("vec4_anglebetween: " << test_vec4_anglebetween());
	LOG("vec4_component: " << test_vec4_component());
	LOG("vec4_project: " << test_vec4_project());
	LOG("vec4_reflect: " << test_vec4_reflect());

	#pragma endregion

	#pragma region mat4_tests

	LOG("mat4_zero: " << test_mat4_zero());
	LOG("mat4_identity: " << test_mat4_identity());
	LOG("mat4_translation: " << test_mat4_translation());
	LOG("mat4_scale: " << test_mat4_scale());
	LOG("mat4_rotation_x: " << test_mat4_rotation_x());
	LOG("mat4_rotation_y: " << test_mat4_rotation_y());
	LOG("mat4_rotation_z: " << test_mat4_rotation_z());
	LOG("mat4_add: " << test_mat4_add());
 	LOG("mat4_sub: " << test_mat4_sub());
 	LOG("mat4_mul_scalar: " << test_mat4_mul_scalar());
 	LOG("mat4_negate: " << test_mat4_negate());
 	LOG("mat4_transpose: " << test_mat4_transpose());
	LOG("vec4_mul_mat4vec4: " << test_vec4_mul_mv());
	LOG("vec4_mul_vec4mat4: " << test_vec4_mul_vm());
	LOG("mat4_mul_mat4mat4: " << test_mat4_mul());
	LOG("mat4_determinant: " << test_mat4_determinant());
 	LOG("mat4_inverse: " << test_mat4_inverse());

	#pragma endregion

	system("Pause");
	return 0;
}
