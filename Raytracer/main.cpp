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

using std::cout;
using std::endl;
using glm::vec3;

int main(){
    scene scene;
    ray line = ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), 25.0f);
    cout << scene.objects[0]->intersects(line) << endl;
    cout << scene.objects[0]->intersectionPoint(line) << endl;
    return 0;
}
