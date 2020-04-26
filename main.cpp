#include <iostream>
#include <application.h>
#include "vec3.h"

float FOV_FACTOR = 320;

const int WINDOW_W = 320;
const int WINDOW_H = 240;

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

            std::cout << SDL_GetTicks() << std::endl;

            for(int i = 0; i < NUM_POINTS;i++) {
                vec3 point = cube_points[i];

                point = vec3_rotate_y(point, cube_rotation.y);
                point = vec3_rotate_x(point, cube_rotation.x);
                point = vec3_rotate_z(point, cube_rotation.z);
                point.z -= vCamera.z;

                projected_points[i] = Project(point);
            }
        }

        void OnDraw() {
            static float x = 0,y = 0;
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_LEFT)) {
                FOV_FACTOR -= 0.5f;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_RIGHT)) {
                cube_rotation.y += 0.001f;
                cube_rotation.x += 0.001f;
                cube_rotation.z == 0.001f;
            }

            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_UP)) {
                y--;
            }
            if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_DOWN)) {
                y++;
            }
            myRenderer->SetColor(1,1,1,1);
            for(int i = 0; i < NUM_POINTS;i++) {
                myRenderer->SetColor(((float)(rand() % 255) / 255), ((float)(rand() % 255) / 255) , ((float)(rand() % 255) / 255), 1); 
                myRenderer->PlotPoint(projected_points[i].x + (WINDOW_W / 2), projected_points[i].y + (WINDOW_H / 2));
            }
        }


    private:
};

int main() {
    App p;
    p.Start(0,0,320,240);
    return 0;
}