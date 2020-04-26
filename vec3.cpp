#include "vec3.h"
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