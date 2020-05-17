#include "matrix.h"

mat4_t mat4_idenity() {
    mat4_t m = {{
                { 1, 0, 0, 0},
                { 0, 1, 0, 0},
                { 0, 0, 1, 0},
                { 0, 0, 0, 1}}};
    return m;
}

mat4_t mat4_make_scale(float x, float y, float z) {
    mat4_t m = mat4_idenity();
    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;
    return m;
}

mat4_t mat4_make_translation(float x, float y, float z) {
    mat4_t m = mat4_idenity();
    m.m[0][3] = x;
    m.m[1][3] = y;
    m.m[2][3] = z;
    return m;
}

vec4 mat4_mul_vec4(mat4_t m, vec4 v) {
    vec4 result;

    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w; 

    return result;
}

mat4_t mat4_make_rotation_z(float a) {
    mat4_t m = mat4_idenity();

    float c = cos(a);
    float s = sin(a);

    m.m[0][0] = c;
    m.m[0][1] = -s;
    m.m[1][0] = s;
    m.m[1][1] = c;

    return m;
};

mat4_t mat4_make_rotation_x(float a) {
    mat4_t m = mat4_idenity();

    float c = cos(a);
    float s = sin(a);

    m.m[1][1] = c;
    m.m[1][2] = -s;
    m.m[2][1] = s;
    m.m[2][2] = c;

    return m;
};

mat4_t mat4_make_rotation_y(float a) {
    mat4_t m = mat4_idenity();

    float c = cos(a);
    float s = sin(a);

    m.m[0][0] = c;
    m.m[0][2] = s;
    m.m[2][0] = -s;
    m.m[2][2] = c;

    return m;
};