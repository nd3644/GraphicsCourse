#ifndef VEC3_H
#define VEC3_H

struct vec3 {
    float x, y, z;
};

vec3 vec3_rotate_x(vec3 v, float angle);
vec3 vec3_rotate_y(vec3 v, float angle);
vec3 vec3_rotate_z(vec3 v, float angle);


#endif