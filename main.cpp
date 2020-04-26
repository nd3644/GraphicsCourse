#include <iostream>
#include <application.h>
#include "vec3.h"
#include "triangle.h"

float FOV_FACTOR = 128.0;

const int WINDOW_W = 320;
const int WINDOW_H = 240;

const int N_MESH_VERTICES = 8;
/*vec3 mesh_vertices[N_MESH_VERTICES] = { 
    {-1, -1, -1}, // 0
    {-1,  1, -1}, // 1
    { 1,  1, -1}, // 2
    { 1, -1, -1}, // 3

    {-1, -1, 1},  // 4
    {-1,  1, 1},  // 5
    { 1,  1, 1},  // 6
    { 1, -1, 1}   // 7
};*/

vec3 mesh_vertices[N_MESH_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};

const int N_MESH_FACES = 6 * 2;
face mesh_faces[N_MESH_FACES] = {
    // front
    { .a = 1, .b = 2, .c = 3 },
    { .a = 1, .b = 3, .c = 4 },
    // right
    { .a = 4, .b = 3, .c = 5 },
    { .a = 4, .b = 5, .c = 6 },
    // back
    { .a = 6, .b = 5, .c = 7 },
    { .a = 6, .b = 7, .c = 8 },
    // left
    { .a = 8, .b = 7, .c = 2 },
    { .a = 8, .b = 2, .c = 1 },
    // top
    { .a = 2, .b = 7, .c = 5 },
    { .a = 2, .b = 5, .c = 3 },
    // bottom
    { .a = 6, .b = 8, .c = 1 },
    { .a = 6, .b = 1, .c = 4 }
};

triangle triangles_to_render[N_MESH_FACES];

class App : public Eternal::Application {
    public:
        static const int NUM_POINTS = 9*9*9;
        vec3 cube_points[NUM_POINTS];
        vec3 projected_points[NUM_POINTS];
        vec3 vCamera = { 0, 0, -5 };
        vec3 cube_rotation = { 0, 0, 0 };

        App() {
        }
        ~App() {

        }

        vec3 Project(vec3 v) {
            vec3 newVec = {
                            ((FOV_FACTOR * v.x) + 0) / v.z,
                            ((FOV_FACTOR * v.y) + 0) / v.z,
                            0 };
            return newVec;
        }

        void OnInitialize() {
            int i = 0;
            for(float x = -1;x <= 1;x += 0.25) {
                for(float y = -1;y <= 1;y += 0.25) {
                    for(float z = -1;z <= 1;z += 0.25) {
                        vec3 new_point = { x, y, z };
                        cube_points[i].x = x;
                        cube_points[i].y = y;
                        cube_points[i].z = z;
                        i++;
                    }
                }
            }
        }

        void OnUpdate() {

            for(int i = 0;i < N_MESH_FACES;i++) {
                face mesh_face = mesh_faces[i];

                vec3 face_verts[3];
                face_verts[0] = mesh_vertices[mesh_face.a-1];
                face_verts[1] = mesh_vertices[mesh_face.b-1];
                face_verts[2] = mesh_vertices[mesh_face.c-1];

                triangle t;
                for(int j = 0;j < 3;j++) {
                    vec3 point = face_verts[j];
                    point = vec3_rotate_x(point, cube_rotation.x);
                    point = vec3_rotate_y(point, cube_rotation.y);
                    point = vec3_rotate_z(point, cube_rotation.z);

                    point.z -= vCamera.z;

                    point = Project(point);
                    point.x += WINDOW_W / 2;
                    point.y += WINDOW_H / 2;

                    t.points[j] = point;
                }
                triangles_to_render[i] = t;

            }

/*            for(int i = 0; i < NUM_POINTS;i++) {
                vec3 point = cube_points[i];

                point = vec3_rotate_y(point, cube_rotation.y);
                point = vec3_rotate_x(point, cube_rotation.x);
                point = vec3_rotate_z(point, cube_rotation.z);
                point.z -= vCamera.z;

                projected_points[i] = Project(point);
            }*/
        }

        void OnDraw() {
            static float x = 0,y = 0;
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_LEFT)) {
                FOV_FACTOR -= 0.5f;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_RIGHT)) {
                cube_rotation.y += 0.01f;
                cube_rotation.x += 0.01f;
                cube_rotation.z == 0.01f;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_UP)) {
                y--;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_DOWN)) {
                y++;
            }

            for(int i = 0;i < N_MESH_FACES;i++) {

            }
/*            myRenderer->SetColor(1,1,1,1);
            for(int i = 0; i < NUM_POINTS;i++) {
                myRenderer->SetColor(((float)(rand() % 255) / 255), ((float)(rand() % 255) / 255) , ((float)(rand() % 255) / 255), 1); 
                myRenderer->PlotPoint(projected_points[i].x + (WINDOW_W / 2), projected_points[i].y + (WINDOW_H / 2));
            }*/

            myRenderer->SetColor(1,1,0,1);
            for(int i = 0;i < N_MESH_FACES;i++) {
                triangle t = triangles_to_render[i];
                myRenderer->PlotPoint(t.points[0].x, t.points[0].y);
                myRenderer->PlotPoint(t.points[1].x, t.points[1].y);
                myRenderer->PlotPoint(t.points[2].x, t.points[2].y);
            }
        }


    private:
};

int main() {
    App p;
    p.Start(0,0,320,240);
    return 0;
}