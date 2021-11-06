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
#include <algorithm>
#include "scene.h"
#include "bitmap_image.hpp"
#include "ray.cpp"

#include<time.h>
#include<stdlib.h>

using std::cout;
using std::endl;
using glm::vec3;


const int SIZEX = 720;
const int SIZEY = 720;

const int MAX_DEPTH = 50;

const float ASPECT = 1.0f;

const float viewport_height = 2.0f;
const float viewport_width = ASPECT * viewport_height;
const float focal_length = 1.0;

const vec3 origin = vec3(0, 0, 0);
const vec3 horizontal = vec3(viewport_width, 0, 0);
const vec3 vertical = vec3(0, viewport_height, 0);
const vec3 lc = origin - horizontal/2.0f - vertical/2.0f + vec3(0, 0, focal_length);

scene scene;
int count_rays = 0;

#define DISTRIBUTED

colour raytrace(ray line, int depth = 0){
    if (depth >= MAX_DEPTH){
        return colour(0, 0, 0);
    }
    count_rays++;
    rayData data = scene.raycast(line);
    
    if (data.object != nullptr){
        if (rand() % 2 == 0){
            line.t = data.distance;
            vec3 direction;
#ifdef DISTRIBUTED
            direction = vec3(0, 0, 0);
            for (int i = 0; i < 10; i++){
                count_rays++;
                direction+= scene.castshadow(data, line).d;
            }
            direction /= 10;
#else
            ray shadow_ray = scene.castshadow(data, line);
            direction = shadow_ray.d;
#endif
            vec3 output_colour =  data.object->baseColour.toVec();
            return colour(glm::min(output_colour / (5.14f *data.object->diffuse) * std::max(0.1f, glm::dot(data.normal,direction)) + pow(std::max(0.0f, glm::dot(data.normal, direction)), data.object->specular), vec3(1.0f, 1.0f, 1.0f)));
        }
        else{
#ifdef DISTRIBUTED
            vec3 average = vec3(0, 0, 0);
            for (int i = 0; i < 2; i++){
                vec3 rDirection = glm::normalize(line.d + glm::dot(line.d, data.normal)*data.normal + vec3(3.0f/(rand()%100) - 1.5f,3.0f/(rand()%100) - 1.5f,3.0f/(rand()%100 - 1.5f)));
                ray reflection_ray = ray(line.e + line.d*data.distance, rDirection, 1);
                
                vec3 output_colour = data.object->baseColour.toVec();
                vec3 trace = raytrace(reflection_ray, depth + 1).toVec();
                if (trace == vec3(0.1f, 0.1f, 0.1f) || trace == vec3(0, 0, 0)){
                    average+= output_colour;
                }
                else average += trace;
                
            }
            return colour(average/10.0f);
#else
            vec3 rDirection = glm::normalize(line.d + glm::dot(line.d, data.normal)*data.normal + vec3(3.0f/(rand()%100) - 1.5f,3.0f/(rand()%100) - 1.5f,3.0f/(rand()%100 - 1.5f)));
            ray reflection_ray = ray(line.e + line.d*data.distance, rDirection, 1);
            vec3 output_colour = data.object->baseColour.toVec();
            vec3 trace = raytrace(reflection_ray, depth + 1).toVec();
            if (trace == vec3(0.1f, 0.1f, 0.1f) || trace == vec3(0, 0, 0)){
                return output_colour;
            }
            return colour(output_colour*(1.0f-data.object->reflectiveness) + data.object->reflectiveness*trace);
#endif

        }
        
    }
    return colour(0.1f, 0.1f, 0.1f);
    
    
}

void getColour(int x, int y, float &r, float &g, float &b){
#ifdef DISTRIBUTED
    const int divisions = 8;
    vec3 rays = vec3(0, 0, 0);
    for (int i = 0; i < divisions; i++){
        for (int j = 0; j < divisions; j++){
            float a = float(x-1) / (SIZEX-1) + float(i)/float(divisions*(SIZEX-1));
            float b = float(y-1) / (SIZEY-1) + float(j)/float(divisions*(SIZEY-1));
            ray line = ray(origin, lc + a*horizontal + b*vertical, 1);
            rays += raytrace(line).toVec();
        }
    }
    colour clr = colour(rays/float(divisions*divisions));
    
#else
    float a = float(x-1) / (SIZEX-1);
    float b = float(y-1) / (SIZEY-1);
    
    ray line = ray(origin, lc + a*horizontal + b*vertical, 1);
    colour clr = raytrace(line).toVec();
    
#endif
    r = clr.r;
    g = clr.g;
    b = clr.b;
}

void render(){
    bitmap_image render(SIZEX, SIZEY);
    
    for (int j = 0; j < SIZEY; j++){
        for (int i =0; i < SIZEX; i++){
            float r = 0.1f;
            float g = 0.1f;
            float b = 0.1f;
            getColour(i, j, r, g, b);
            render.set_pixel(i, j, 255*r, 255*g, 255*b);
        }
    }
    render.save_image("./render.bmp");
}

int main(){
    srand(time(NULL));
    render();
    cout << "Number of Rays: " << count_rays << endl;
    return 0;
}
