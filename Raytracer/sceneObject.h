//
//  object.h
//  GraphicsAssignment1
//
//  Created by Kashif Hussain on 2021-10-31.
//

#ifndef object_h
#define object_h

#include <string>
#include <utility>

#include <glm/glm.hpp>
#include "ray.hpp"

using glm::vec3;
using std::pair;
using std::string;

struct colour{
    float r, g, b;
    colour(float red, float green, float blue)
    :r(red)
    ,g(green)
    ,b(blue){};
    colour(vec3 col)
    :r(col.r),
    g(col.g),
    b(col.b){};
    vec3 toVec(){return vec3(r, g, b);};
};

class sceneObject {
protected:
    float getDiscriminant(float a, float b, float c);
    pair<float, float> solveQuadratic(float a, float b, float c, float disc);
public:
    sceneObject(vec3 object_position)
    :position{object_position}{
        
    };
    vec3 position;
    colour baseColour = colour(1.0f, 1.0f, 1.0f);
    float diffuse = 0.4f;
    float specular = 20.0f;
    float reflectiveness = 0.05f;
    virtual bool intersects(ray line) {return false;};
    virtual float intersectionPoint (ray line) {return -1.0f;};
    virtual vec3 getNormal(ray line) = 0;
    virtual string getName() = 0;
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
    virtual vec3 getNormal(ray line) override;
    virtual string getName() override {return "Sphere";};
    
};

class plane : public sceneObject{
    vec3 normal;
public:
    plane(vec3 object_position, vec3 n) : sceneObject{object_position}, normal(n)
    {
        
    };
    virtual bool intersects(ray line) override;
    virtual float intersectionPoint(ray line) override;
    virtual vec3 getNormal(ray line) override;
    virtual string getName() override {return "Plane";};
};

#endif /* object_h */
