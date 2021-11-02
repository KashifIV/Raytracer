//
//  object.cpp
//  GraphicsAssignment1
//
//  Created by Kashif Hussain on 2021-10-31.
//

#include "sceneObject.h"
#include <math.h>
#include <utility>
#include <glm/glm.hpp>

using std::pair;

float sceneObject::getDiscriminant(float a, float b, float c){
    return b * b - 4 * a * c;
}

pair<float, float> sceneObject::solveQuadratic(float a, float b, float c, float disc){
    float r1, r2;
    
    if (disc == 0){
        r1 = -b/ 2*a;
        return pair<float, float>(r1, r1);
    }
    
    r1 = (-b + sqrt(disc))/2*a;
    r2 = (-b - sqrt(disc))/2*a;
    
    if (r1 < r2){
        return pair<float, float>(r1, r2);
    }
    else{
        return pair<float, float>(r2, r1);
    }
    
}

pair<float, float> sphere::intersection(ray line){
    vec3 ec = line.e - position;
    float a = glm::dot(line.d, line.d);
    float b = glm::dot(2.0f*line.d, ec);
    float c = glm::dot(ec, ec) - radius* radius;
    
    float disc = getDiscriminant(a, b, c);
    if (disc < 0){
        return pair<float, float>(-1.0f, -1.0f);
    }
    
    return solveQuadratic(a, b, c, disc);
}

bool sphere::intersects(ray line){
    pair<float, float> values = intersection(line);
    
    if(values.first < 0 && values.second < 0){
        return false;
    }
    return true;
}

float sphere::intersectionPoint(ray line){
    pair<float, float> values = intersection(line);
    
    if(values.first < 0 && values.second < 0){
        return 0;
    }
    if (values.first > 0){
        return values.first;
    }
    else{
        return values.second;
    }
}

vec3 sphere::getNormal(ray line){
    return (line.getPoint() - position) / radius;
}
