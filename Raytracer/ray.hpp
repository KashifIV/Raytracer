//
//  ray.hpp
//  GraphicsAssignment1
//
//  Created by Kashif Hussain on 2021-10-31.
//

#ifndef ray_hpp
#define ray_hpp

#include <stdio.h>
#include <glm/glm.hpp>

using glm::vec3;

class ray{
public:
    ray(vec3 position, vec3 direction, float param)
    :e(position)
    ,d(direction)
    ,t(param){};
    
    vec3 e, d;
    float t;
};
#endif /* ray_hpp */
