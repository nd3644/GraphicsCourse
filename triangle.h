#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"

struct face {
    int a;
    int b;
    int c;
};

struct triangle {
    vec3 points[3];
    vec3 n;
};

#endif