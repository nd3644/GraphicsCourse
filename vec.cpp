#include "vec.h"
#include <math.h>

vec3 vec3_rotate_x(vec3 v, float angle) {
    vec3 rotated;
    rotated.x = v.x;
    rotated.y = v.y * cos(angle) - v.z * sin(angle);
    rotated.z = v.y * sin(angle) + v.z * cos(angle);
    return rotated;
}

vec3 vec3_rotate_y(vec3 v, float angle) {
    vec3 rotated;
    rotated.x = v.x * cos(angle) - v.z * sin(angle);
    rotated.y = v.y;
    rotated.z = v.x * sin(angle) + v.z * cos(angle);
    return rotated;
}

vec3 vec3_rotate_z(vec3 v, float angle) {
    vec3 rotated;
    rotated.x = v.x * cos(angle) - v.y * sin(angle);
    rotated.y = v.x * sin(angle) + v.y * cos(angle);
    rotated.z = v.z;
    return rotated;
}

vec3 vec3_mul(vec3 a, float scalar) {
    vec3 v = { a.x * scalar, a.x * scalar, a.z * scalar };
    return v;
}

vec2 vec2_add(vec2 a, vec2 b) {
    vec2 v = { a.x + b.x, a.y + b.y };
    return v;
}

vec2 vec2_sub(vec2 a, vec2 b) {
    vec2 v = { a.x - b.x, a.y - b.y };
    return v;
}

vec2 vec2_mul(vec2 a, float scalar) {
    vec2 v = { a.x * scalar, a.y * scalar };
    return v;
}

vec2 vec2_div(vec2 a, float scalar) {
    vec2 v = { a.x / scalar, a.y / scalar };
    return v;
}

float vec2_length(vec2 v) {
    return sqrtf((v.x * v.x) + (v.y * v.y));
}

float vec3_length(vec3 v) {
    return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

vec3 vec3_add(vec3 a, vec3 b) {
    vec3 v = { a.x + b.x, a.y + b.y, a.z + b.z };
    return v;
}

vec3 vec3_sub(vec3 a, vec3 b) {
    vec3 v = { a.x - b.x, a.y - b.y, a.z - b.z };
    return v;
}

vec3 vec3_div(vec3 a, float scalar) {
    vec3 v = {a.x / scalar, a.y / scalar, a.z / scalar};
    return v;
}



