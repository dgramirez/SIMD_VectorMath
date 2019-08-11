#ifndef __MAT_TEST_H
#define __MAT_TEST_H

#include "tMath.h"

bool test_mat4_zero();
bool test_mat4_identity();
bool test_mat4_translation();
bool test_mat4_scale();
bool test_mat4_rotation_x();
bool test_mat4_rotation_y();
bool test_mat4_rotation_z();
bool test_mat4_add();
bool test_mat4_sub();
bool test_mat4_mul_scalar();
bool test_mat4_negate();
bool test_mat4_transpose();
bool test_vec4_mul_vm();
bool test_vec4_mul_mv();
bool test_mat4_mul();
bool test_mat4_determinant();
bool test_mat4_inverse();

#endif