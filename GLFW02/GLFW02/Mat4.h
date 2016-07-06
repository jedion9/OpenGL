//
//  Mat4.h
//  GLFW02
//
//  Created by Alex Register on 7/4/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef Mat4_h
#define Mat4_h

/*
 One of the main things about this structure is that it is going to have to work with this function:
 
    glUniformMatrix4fv( GLint location, GLsizei count, GLboolean transpose, const GLfloat *value );
 
    GLint location: retrieved by finding the location of the mat4 variable by using this:
                    GLuint location = glGetUniformLocation(shaderprogram, varible name);
 
    GLsizei count: Tutorial always uses '1'.
    
    GLboolean transpose: Tutorial always uses GL_FALSE.
 
    const GLFloat *value: Here is where we will have to know how GLSL wants the mat4 type given to it.
 
 */
#include "Vec3.h"

struct Mat4{
    float numbers[4][4];
};

void mat4Identity( struct Mat4 *m){

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(i == j){ m->numbers[i][j] = 1;}
            else{ m->numbers[i][j] = 0; }
        }
    }
    
}

void mat4Translate(struct Mat4 *m, struct Vec3 *v){

    m->numbers[0][3] = v->verticies[0];
    m->numbers[1][3] = v->verticies[1];
    m->numbers[2][3] = v->verticies[2];

}

void multiply(struct Mat4 *m, struct Vec4 *v){

    struct Vec4 tempVec;
    for(int i = 0; i < 4; i++){ tempVec.verticies[i] = 0; }
    
    for(int r = 0; r < 4; r++){         // 4 times ->Columns
        for(int c = 0; c < 4; c++){     //16 times ->Rows
            tempVec.verticies[r] += m->numbers[r][c] * v->verticies[c];
        }
    }
    
    for(int i = 0; i < 4; i++){ v->verticies[i] = tempVec.verticies[i]; }
    
}

void printMat4(struct Mat4 *m){

    for(int r = 0; r < 4; r++){         // 4 times ->Columns
        for(int c = 0; c < 4; c++){     //16 times ->Rows
            printf(" %.1f, ", m->numbers[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    
}

#endif /* Mat4_h */
