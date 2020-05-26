#include "mesh.h"
#include <iostream>
#include <sstream>

// helper function to determine if face is defined i/i/i or i//i
bool obj_contain_double_slash(std::string sLine) {
    for(int i = 0;i < sLine.size();i++) {
        if(sLine[i] == '/' && sLine.size() < i + 1) {
            if(sLine[i+1] == '/') {
                return true;
            }
        }
    }
    return false;
}

int obj_count_slashes(std::string sLine) {
    int count = 0;
    for(int i = 0;i < sLine.size();i++) {
        if(sLine[i] == '/') {
            count++;
        }
    }
    std::cout << "count :" << count << std::endl;
    return count;
}

void load_obj(std::string sfilename, mesh &myMesh) {
    myMesh.verts.clear();
    myMesh.faces.clear();

    std::ifstream infile;
    infile.open(sfilename);
    if(infile.fail()) {
        printf("failed to open obj");
        return;
    }

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
            myMesh.verts.push_back(v);
        }
        else if(tmp == "f") {
            int i = 0;
            f.color = 0xFFFFFFFF;
            std::sscanf(sLine.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &f.a, &i, &i, &f.b, &i, &i, &f.c, &i, &i);
            myMesh.faces.push_back(f);
        }
    }

    infile.close();
}