#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"
#include <stdint.h>

struct face {
    int a;
    int b;
    int c;
    uint32_t color;
};

struct triangle {
    vec3 points[3];
    vec3 n;
    uint32_t color;
};

#endif