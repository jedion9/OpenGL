//
//  Vec4.h
//  GLFW02
//
//  Created by Alex Register on 7/4/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef Vec4_h
#define Vec4_h

/*
 
 This is just a quick build of the Vec4 struct to get as close to HOW it is coded in C++.
 There is a demo of the code in main.c @ about line 21-22.
 
 */

struct Vec4{
    float verticies[4];
};

//In order to make changes to the struct without the results being lost, you must use the pointer
//as an argument otherwise the results will be lost once the function is finished.

void newVec4(struct Vec4 *vec, float x, float y, float z, float w){
    vec->verticies[0] = x;
    vec->verticies[1] = y;
    vec->verticies[2] = z;
    vec->verticies[3] = w;
}

//This is just to demonstrate that you cannot have a function name be the same as one that already
//Exists even though it requires different parameters.


//void vec(int g){


//}

void printVec4(struct Vec4 *v){

    printf(" %.1f, %.1f, %.1f, %.1f \n\n", v->verticies[0], v->verticies[1], v->verticies[2], v->verticies[3]);
    
}

#endif /* Vec4_h */
