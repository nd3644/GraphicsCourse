#ifndef MESH_H
#define MESH_H

#include "vec3.h"
#include "triangle.h"
#include <vector>

struct mesh {
    std::vector<vec3>verts;
    std::vector<face>faces;
    vec3 rotation;
};

#endif