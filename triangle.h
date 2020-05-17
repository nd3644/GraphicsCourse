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
    triangle() {
        avg_z = 0;
        color = 0x00;
        n = { 0, 0, 0 };
        for(int i = 0;i < 3;i++){
            points[i] = { 0, 0, 0 };
        }
    }
    vec3 points[3];
    vec3 n;
    uint32_t color;
    float avg_z;
};

#endif