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

class scene {
    
public:
    vector<sceneObject*> objects;
    scene(){
        sceneObject* item1 = new sphere(glm::vec3(0, 0, 20), 100);
        objects.push_back(item1);
    };
    
};

#endif /* scene_h */
