//
//  scene.cpp
//  Raytracer
//
//  Created by Kashif Hussain on 2021-11-01.
//

#include "scene.h"
#include <iostream>
#include<time.h>
#include<stdlib.h>

#define inf 0x3f3f3f

using std::cout;
using std::endl;

rayData scene::raycast(ray ray){
    vector<rayData> intersections;
    for (int i = 0; i < objects.size(); i++){
        if (objects[i]->intersects(ray)){
            rayData data;
            data.object = objects[i];
            data.distance = objects[i]->intersectionPoint(ray);
            ray.t = data.distance;
            data.normal = objects[i]->getNormal(ray);
            intersections.push_back(data);
        }
    }
    rayData min;
    min.distance = inf;
    for (int i = 0; i < intersections.size(); i++){
        if (intersections[i].distance < min.distance){
            min = intersections[i];
        }
    }
    return min;
}

bool scene::isLit(vec3 point){
    
    
    sceneObject* light = lights[rand() % lights.size()];
    
    vec3 target = light->position;
    
    target.x += float(rand()%50) - 25 / 100.0f;
    //target.y += float(rand()%50) - 25 / 200.0f;
    target.z += float(rand()%50) - 25 / 100.0f;
    vec3 direction = target - point;
    float magnitude = sqrt(direction.x * direction.x + direction.y*direction.y + direction.z*direction.z);
    ray shadow_ray = ray(point, direction/magnitude, 1);
    
    float light_distance = light->intersectionPoint(shadow_ray);
    
    for (int i = 0; i < objects.size(); i++){
        if (objects[i]->intersects(shadow_ray)){
            if (0 < objects[i]->intersectionPoint(shadow_ray) < light_distance){
                return false;
            }
        }
    }
    
    return true;
}

ray scene::castshadow(rayData data, ray line){

    vec3 point = line.getPoint();
    colour object_colour = data.object->baseColour;
    
    sceneObject* light = lights[rand() % lights.size()];
    
    vec3 target = light->position;
    
    target.x += float(rand()%100) - 50.0f;
    target.z += float(rand()%100) - 50.0f;
    
    vec3 direction = target - point;
    float magnitude = sqrt(direction.x * direction.x + direction.y*direction.y + direction.z*direction.z);
    ray shadow_ray = ray(point, direction/magnitude, 1);

    
    float light_distance = light->intersectionPoint(shadow_ray);
    
    for (int i = 0; i < objects.size(); i++){
        if (objects[i]->intersects(shadow_ray) && objects[i] != data.object){
            if (0.2f < objects[i]->intersectionPoint(shadow_ray) < light_distance){
                shadow_ray.d = vec3(0, 0, 0);
                return shadow_ray;
            }
        }
    }
    return shadow_ray;

}
