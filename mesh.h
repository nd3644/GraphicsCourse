#ifndef MESH_H
#define MESH_H

#include "vec.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>

struct mesh {
    std::vector<vec3>verts;
    std::vector<face>faces;
    vec3 rotation;
};

extern void load_obj(std::string sfilename, mesh &myMesh);

#endif