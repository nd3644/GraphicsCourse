#ifndef MESH_H
#define MESH_H

#include "vec.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>

struct mesh {
    mesh() {
        rotation = { 0, 0, 0 };
        translation = { 0, 0, 0};
        scale = { 1, 1, 1 };
    }
    std::vector<vec3>verts;
    std::vector<face>faces;
    vec3 rotation;
    vec3 translation;
    vec3 scale;
};

extern void load_obj(std::string sfilename, mesh &myMesh);

#endif