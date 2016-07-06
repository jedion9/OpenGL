//
//  Vec3.h
//  GLFW02
//
//  Created by Alex Register on 7/5/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef Vec3_h
#define Vec3_h

struct Vec3{
    float verticies[3];
};

//In order to make changes to the struct without the results being lost, you must use the pointer
//as an argument otherwise the results will be lost once the function is finished.

void newVec3(struct Vec3 *vec, float x, float y, float z){
    vec->verticies[0] = x;
    vec->verticies[1] = y;
    vec->verticies[2] = z;
}


#endif /* Vec3_h */
