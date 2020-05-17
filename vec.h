#ifndef VEC3_H
#define VEC3_H

struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x, y, z;
};

struct vec4 {
    float x, y, z, w;
};

vec3 vec3_rotate_x(vec3 v, float angle);
vec3 vec3_rotate_y(vec3 v, float angle);
vec3 vec3_rotate_z(vec3 v, float angle);


vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float scalar);
vec2 vec2_div(vec2 a, float scalar);
vec2 vec2_normalize(vec2 v);
float vec2_dot(vec2 a);


float vec3_length(vec3 v);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, float scalar);
vec3 vec3_div(vec3 a, float scalar);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_normalize(vec3 v);
float vec3_dot(vec3 a, vec3 b);


vec4 vec4_from_vec3(vec3 v);
vec3 vec3_from_vec4(vec4 v);


#endif