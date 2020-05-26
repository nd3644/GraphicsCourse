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

mat4_t mat4_mul_mat4(mat4_t a, mat4_t b) {
    mat4_t m = mat4_idenity();
    for(int i = 0;i < 4;i++) {
        for(int j = 0;j < 4;j++) {
            m.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
        }
    }
    return m;
}

mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar) {
    mat4_t m = {{{ 0 }}};

    const float half_fov = fov / 2;

    m.m[0][0] = aspect * (1 / tan(half_fov));
    m.m[1][1] = 1 / tan(half_fov);
    m.m[2][2] = zfar / (zfar - znear);
    m.m[2][3] = (-zfar * znear) / (zfar - znear);
    m.m[3][2] = 1.0f;

    return m;
}

vec4 mat4_mul_vec4_project(mat4_t mat_proj, vec4 v) {
    vec4 result = mat4_mul_vec4(mat_proj, v);

    if(result.w != 0) {
        result.x /= result.w;
        result.y /= result.w;
        result.z /= result.w;
    }

    return result;
}

mat4_t mat4_look_at(vec3 eye, vec3 target, vec3 up) {
    vec3 z = vec3_sub(target, eye); z = vec3_normalize(z);      // forward
    vec3 x = vec3_cross(up, z);     x = vec3_normalize(x);      // right
    vec3 y = vec3_cross(z, x);      y = vec3_normalize(y);      // up

    mat4_t view_matrix = {{
            { x.x, x.y, x.z }, 
            { y.x, y.y, y.z }, 
            { z.x, z.y, z.z },
            {0, 0, 0, 1} }};

    return view_matrix;
}
