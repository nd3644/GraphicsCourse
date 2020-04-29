#ifndef VEC3_H
#define VEC3_H

struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x, y, z;
};

vec3 vec3_rotate_x(vec3 v, float angle);
vec3 vec3_rotate_y(vec3 v, float angle);
vec3 vec3_rotate_z(vec3 v, float angle);


float vec2_length(vec2 v);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float scalar);
vec2 vec2_div(vec2 a, float sclar);


float vec3_length(vec3 v);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, float scalar);
vec3 vec3_div(vec3 a, float scalar);

#endif