/************************************************
 *
 *          CSCI 4110 Laboratory One
 *
 *  This program is a skeleton that can be used
 *  to evaluate different shader programs.  You
 *  don't need to modify any of the code.  But, please
 *  take a look at the code so you can refresh your
 *  memory on OpenGL programming.
 *
 ************************************************/

#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "scene.h"
#include "bitmap_image.hpp"
#include "ray.cpp"
using std::cout;
using std::endl;
using glm::vec3;

const int SIZEX = 1280;
const int SIZEY = 720;
scene scene;

struct rayData{
    sceneObject* object;
    float distance;
};


vector<rayData> raycast(ray ray){
    vector<rayData> points;
    for (int i = 0; i < scene.objects.size(); i++){
        if (scene.objects[i]->intersects(ray)){
            rayData data;
            data.object = scene.objects[i];
            data.distance = scene.objects[i]->intersectionPoint(ray);
            points.push_back(data);
        }
    }
    return points;
}
void getColour(int x, int y, float &r, float &g, float &b){
    ray line = ray(vec3(x - SIZEX/2, y - SIZEY/2, 0), vec3(0.0f, 0.0f, 1.0f), 1);
    vector<rayData> data = raycast(line);
    if (data.size() > 0){
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
    }
}

void render(){
    bitmap_image render(SIZEX, SIZEY);
    
    for (int i = 0; i < SIZEX; i++){
        for (int j =0; j < SIZEY; j++){
            float r = float(i) / float(SIZEX);
            float g = float(j)/float(SIZEY);
            float b = 0.4;
            getColour(i, j, r, g, b);
            render.set_pixel(i, j, 255*r, 255*g, 255*b);
        }
    }
    render.save_image("./render.bmp");
}

int main(){
    
    render();
    ray line = ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), 25.0f);
    cout << scene.objects[0]->intersects(line) << endl;
    cout << scene.objects[0]->intersectionPoint(line) << endl;
    cout << "hello" << endl;
    return 0;
}
