//
//  scene.h
//  GraphicsAssignment1
//
//  Created by Kashif Hussain on 2021-10-31.
//

#ifndef scene_h
#define scene_h

#include <vector>
#include "sceneObject.h"


using std::vector;

struct rayData{
    sceneObject* object = nullptr;
    float distance;
    vec3 normal;
};

class scene {
    
public:
    vector<sceneObject*> objects;
    vector<sceneObject*> lights;
    scene(){
        sceneObject* item1 = new sphere(glm::vec3(-10, 0, 20), 5);
        item1->baseColour = colour(1, 0, 0);
        objects.push_back(item1);
        objects.push_back( new sphere(glm::vec3(10, 0, 20), 5));
        objects[1]->baseColour = colour(0, 1, 0);
        objects.push_back( new sphere(glm::vec3(0, 0, 30), 5));
        objects[2]->reflectiveness = 1.0f;

        sceneObject* item2 = new plane(glm::vec3(0, 9, 20), glm::vec3(0, -1.0, 0));
        item2->baseColour = colour(0, 0, 1);
        objects.push_back(item2);
        
        sceneObject* light = new plane(glm::vec3(0, -100, 20), glm::vec3(0, 1, 0));
        lights.push_back(light);
    };
    rayData raycast(ray ray);
    bool isLit(vec3 point);
    ray castshadow(rayData data, ray line);
    
};

#endif /* scene_h */
