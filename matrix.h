#ifndef MATRIX_H
#define MATRIX_H

#include "vec.h"
#include <math.h>

struct mat4_t {
    float m[4][4];
};


mat4_t mat4_idenity();

mat4_t mat4_make_scale(float x, float y, float z);
mat4_t mat4_make_translation(float x, float y, float z);
mat4_t mat4_mul_mat4(mat4_t a, mat4_t b);

mat4_t mat4_make_rotation_z(float a);
mat4_t mat4_make_rotation_x(float a);
mat4_t mat4_make_rotation_y(float a);
vec4 mat4_mul_vec4(mat4_t m, vec4 v);

mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar);
vec4 mat4_mul_vec4_project(mat4_t mat_proj, vec4 v);

mat4_t mat4_look_at(vec3 eye, vec3 target, vec3 up);

#endif
