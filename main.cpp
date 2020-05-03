#include <iostream>
#include <vector>
#include <application.h>
#include "vec.h"
#include "triangle.h"
#include "mesh.h"

float FOV_FACTOR = 640.0;

const int WINDOW_W = 320;
const int WINDOW_H = 240;

const int N_CUBE_VERTICES = 8;
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

vec3 cube_vertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};

const int N_CUBE_FACES = 6 * 2;
face cube_faces[N_CUBE_FACES] = {
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

std::vector<triangle>triangles_to_render;

class App : public Eternal::Application {
    public:
        static const int NUM_POINTS = 9*9*9;
        vec3 cube_points[NUM_POINTS];
        vec3 projected_points[NUM_POINTS];
        vec3 vCamera = { 0, 0, -20 };
        mesh myMesh;

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

        void DrawLine(int x0, int y0, int x2, int y2) {
            int delta_x = x2 - x0;
            int delta_y = y2 - y0;

            int side_length = (abs(delta_x) > abs(delta_y)) ? abs(delta_x) : abs(delta_y);

            float xinc = delta_x / (float)side_length;
            float yinc = delta_y / (float)side_length;

            float x = x0;
            float y = y0;
            myRenderer->SetColor(0,0,1,1);
            for(int i = 0;i < side_length;i++) {
                myRenderer->PlotPoint((int)x,(int)y);
                x += xinc;
                y += yinc;
            }
        }


        void DrawTriangle(triangle t) {
            myRenderer->SetColor(0,0,1,1);

            DrawFilledTriangle(t.points[0].x, t.points[0].y,t.points[1].x, t.points[1].y,t.points[2].x, t.points[2].y);
        }

        void load_cube_data() {
            for(int i = 0;i < N_CUBE_FACES;i++) {
                myMesh.faces.push_back(cube_faces[i]);
            }
            for(int i = 0;i < N_CUBE_VERTICES;i++) {
                myMesh.verts.push_back(cube_vertices[i]);
            }
        }

        void OnInitialize() {
            load_cube_data();
            load_obj("data/cube.obj", myMesh);

            vec3 a = { 2.5, 6.4, 3.0 };
            vec3 b = { -2.2, 1.4, -1.0 };

            std::cout << "a: " << vec3_length(a) << std::endl;
            std::cout << "b: " << vec3_length(b) << std::endl;
        }

        void OnUpdate() {

            if(myInputHandle->IsKeyTap(Eternal::InputHandle::KEY_ESCAPE)) {
                exit(0);
            }

            for(int i = 0;i < myMesh.faces.size();i++) {
                face mesh_face = myMesh.faces[i];

                vec3 face_verts[3];
                face_verts[0] = myMesh.verts[mesh_face.a-1];
                face_verts[1] = myMesh.verts[mesh_face.b-1];
                face_verts[2] = myMesh.verts[mesh_face.c-1];

                triangle t;
                vec3 transformed_verts[3];  
                for(int j = 0;j < 3;j++) {
                    vec3 point = face_verts[j];

                    point = vec3_rotate_x(point, myMesh.rotation.x);
                    point = vec3_rotate_y(point, myMesh.rotation.y);
                    point = vec3_rotate_z(point, myMesh.rotation.z);

                    point.z -= vCamera.z;

                    transformed_verts[j] = point;
                }

                vec3 ba = vec3_sub(transformed_verts[1], transformed_verts[0]);
                ba = vec3_normalize(ba);
                vec3 ca = vec3_sub(transformed_verts[2], transformed_verts[0]);
                ca = vec3_normalize(ca);

                vec3 n = vec3_cross(ba, ca);
                n = vec3_normalize(n);
                t.n = n;

                vec3 camera_ray = vec3_sub(vCamera, transformed_verts[0]);
                if(vec3_dot(camera_ray, n) < 0) {
                    continue;
                }

                for(int j = 0;j < 3;j++) {
                    vec3 point = transformed_verts[j];

                    point = Project(point);
                    point.x += WINDOW_W / 2;
                    point.y += WINDOW_H / 2;

                    t.points[j] = point;
                }
                t.n = Project(t.n);
                t.n.x += WINDOW_W / 2;
                t.n.y += WINDOW_H / 2;
                triangles_to_render.push_back(t);
            }
        }

        float GetLineSlope(float x, float y, float x1, float y1) {
            float delta_x = x - x1;
            float delta_y = y - y1;

            return delta_x / delta_y;
        }

        void fill_flat_bottom(float x0, float y0, float x1, float y1, float x2, float y2) {
            float slope1 = GetLineSlope(x2,y2,x0,y0);
            float slope2 = GetLineSlope(x1,y1,x0,y0);

            float startX = x0;
            float endX = x0;
            myRenderer->SetColor(0,0,1,1);
            for(int y = y0;y <= y2;y++) {
                DrawLine(startX, y, endX, y);
                startX += slope1;
                endX += slope2;
            }
        }

        void fill_flat_top(float x0, float y0, float x1, float y1, float x2, float y2) {
            float slope1 =  GetLineSlope(x2,y2,x0,y0);
            float slope2 = GetLineSlope(x2,y2, x1, y1);

            float startX = x2;
            float endX = x2;
            myRenderer->SetColor(0,0,1,1);
            for(int y = y2;y >= y0;y--) {
                DrawLine(startX, y, endX, y);
                startX -= slope1;
                endX -= slope2;
            }

        }

        void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
            if(y0 > y1) {
                std::swap(y0, y1);
                std::swap(x0, x1);
            }

            if(y1 > y2) {
                std::swap(y1, y2);
                std::swap(x1, x2);
            }

            if(y0 > y1) {
                std::swap(y0, y1);
                std::swap(x0, x1);
            }

            if(y1 == y2) {
                fill_flat_bottom(x0, y0, x1, y1, x2, y2);
                return;
            }
            if(y0 == y1) {
                fill_flat_top(x0, y0, x1, y1, x2, y2);
                return;
            }

            int mY = y1;
            int mX = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

            fill_flat_bottom(x0, y0, x1, y1, mX, mY);
            fill_flat_top(x1, y1, mX, mY, x2, y2);

/*            myRenderer->SetColor(1,1,1,1);
            myRenderer->DrawLine(x0, y0, x1, y1);
            myRenderer->DrawLine(x0, y0, x2, y2);
            myRenderer->DrawLine(x1, y1, x2, y2);

            myRenderer->SetColor(1,0,0,1);
            myRenderer->PlotPoint(x0, y0);

            myRenderer->SetColor(0,1,0,1);
            myRenderer->PlotPoint(x1, y1);

            myRenderer->SetColor(0,0,1,1);
            myRenderer->PlotPoint(x2, y2);*/


        }

        void OnDraw() {

            vec3 poots[3] = { { 32, 0 } , { 64, 100 }, {0, 64} }; 

            static float fx = 300;
            static float fy = 300;

            static float r = 0;
            for(int i = 0;i < 3;i++ ){
                poots[i] = vec3_rotate_z(poots[i], r);
                poots[i].x += fx;
                poots[i].y += fy;
            }

            DrawFilledTriangle((int)poots[0].x, (int)poots[0].y, (int)poots[1].x, (int)poots[1].y, (int)poots[2].x, (int)poots[2].y); 

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_LEFT)) {
                fx--;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_RIGHT)) {
                fx++;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_UP)) {
                fy--;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_DOWN)) {
                fy++;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::BUTTON_A)) {
                r += 0.01f;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::BUTTON_B)) {
                r -= 0.01f;
            }

            static float x = 0,y = 0;
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_LEFT)) {
                FOV_FACTOR += 5.0f;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_RIGHT)) {
                myMesh.rotation.x += 0.01f;
                myMesh.rotation.y += 0.01f;
                myMesh.rotation.z += 0.01f;
            }
/*
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_UP)) {
                y--;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_DOWN)) {
                y++;
            }*/


/*            myRenderer->SetColor(1,1,1,1);
            for(int i = 0; i < NUM_POINTS;i++) {
                myRenderer->SetColor(((float)(rand() % 255) / 255), ((float)(rand() % 255) / 255) , ((float)(rand() % 255) / 255), 1); 
                myRenderer->PlotPoint(projected_points[i].x + (WINDOW_W / 2), projected_points[i].y + (WINDOW_H / 2));
            }*/

            myRenderer->SetColor(1,1,0,1);
            for(int i = 0;i < triangles_to_render.size();i++) {
                triangle t = triangles_to_render[i];

                DrawTriangle(t);
            }
            triangles_to_render.clear();
        }


    private:
};

int main() {
    App p;
    p.Start(0,0,WINDOW_W,WINDOW_H);
    return 0;
}