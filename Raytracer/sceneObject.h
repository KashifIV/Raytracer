//
//  object.h
//  GraphicsAssignment1
//
//  Created by Kashif Hussain on 2021-10-31.
//

#ifndef object_h
#define object_h

#include <utility>

#include <glm/glm.hpp>
#include "ray.hpp"

using glm::vec3;
using std::pair;

class sceneObject {
protected:
    vec3 position;
    float getDiscriminant(float a, float b, float c);
    pair<float, float> solveQuadratic(float a, float b, float c, float disc);
public:
    sceneObject(vec3 object_position)
    :position{object_position}{
        
    };
    virtual bool intersects(ray line) {return false;};
    virtual float intersectionPoint (ray line) {return -1.0f;};
};

class sphere : public sceneObject {
    float radius;
    pair<float, float> intersection(ray line);
public:
    sphere(vec3 object_position, float sphere_radius)
    :sceneObject{object_position}
    ,radius{sphere_radius}
    {

    };
    virtual bool intersects(ray line) override;
    virtual float intersectionPoint(ray line) override;
};

//class plane: public sceneObject{
//public:
//    plane(vec3 object_position)
//    :sceneObject(object_position){
//
//    };
//    bool intersects(ray line) override;
//    float intersectionPoint(ray line) override;
//};

#endif /* object_h */
