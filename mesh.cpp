#include "mesh.h"
#include <iostream>
#include <sstream>

void load_obj(std::string sfilename, mesh &myMesh) {
    myMesh.verts.clear();
    myMesh.faces.clear();

    std::ifstream infile;
    infile.open(sfilename);

    vec3 v = { 0, 0, 0 };
    face f = { 0, 0, 0 };

    while(!infile.eof()) {
        std::string sLine;
        std::getline(infile, sLine);

        std::stringstream ss(sLine);

        std::string tmp;
        ss >> tmp;
        if(tmp == "v") {
            ss >> v.x; ss >> v.y; ss >> v.z;
            std::cout << v.x << " " << v.y << " " << v.z << std::endl;
            myMesh.verts.push_back(v);
        }
        else if(tmp == "f") {
            int i = 0;
            std::sscanf(sLine.c_str(), "f %d/%d %d/%d %d/%d", &f.a, &i, &f.b, &i, &f.c, &i);
            std::cout << f.a << " , " << f.b << " , " << f.c << std::endl;
            myMesh.faces.push_back(f);
        }
    }

    infile.close();
    std::cout << "verts: " << myMesh.verts.size() << std::endl;
    std::cout << "faces: " << myMesh.faces.size() << std::endl;
}