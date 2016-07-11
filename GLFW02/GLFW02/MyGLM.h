//
//  MyGLM.h
//  GLFW02
//
//  Created by Alex Register on 7/7/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef MyGLM_h
#define MyGLM_h

#include <math.h>

/*These are used in conjunction with setMat4(Mat4, int); */

const int EMPTY = 0;
const int IDENTITY = 1;

typedef struct Vector3{ float verticies[3]; } Vec3;

typedef struct Vector4{ float verticies[4]; } Vec4;

typedef struct Matrix4x4{ float numbers[4][4]; } Mat4;

/* Populates an array of 3 values */
void newVec3(Vec3 *vec, float x, float y, float z);

/* Populates an array of 4 values */
void newVec4(Vec4 *vec, float x, float y, float z, float w);

/* Sets a type Mat4 to a set Matrix type.  Types listed below:
    EMPTY:      [ 0 0 0 0 ]
                [ 0 0 0 0 ]
                [ 0 0 0 0 ]
                [ 0 0 0 0 ]
 
    IDENTITY:   [ 1 0 0 0 ]
                [ 0 1 0 0 ]
                [ 0 0 1 0 ]
                [ 0 0 0 1 ]
 */
void setMat4(Mat4 *m, int matrixType);

/* */
void translate(Mat4 *m, Vec3 *v);
void scale(Mat4 *m, Vec3 *v);
void rotate(Mat4 *m, float degrees, Vec3 *v);
void Mat4XVec4(Mat4 *m, Vec4 *v);
void Mat4CopyMat4(Mat4 *m1, Mat4 *m2);
void Mat4XMat4(Mat4 *m1, Mat4 *m2);
void printMat4(Mat4 *m);
//Add all other methods???


void newVec3(Vec3 *vec, float x, float y, float z){
    vec->verticies[0] = x;
    vec->verticies[1] = y;
    vec->verticies[2] = z;
}

void newVec4(Vec4 *vec, float x, float y, float z, float w){
    vec->verticies[0] = x;
    vec->verticies[1] = y;
    vec->verticies[2] = z;
    vec->verticies[3] = w;
}

void setMat4(Mat4 *m, int matrixType){

    switch(matrixType){
            
        case 0:
            
            for(int r = 0; r < 4; r++){
                for(int c = 0; c < 4; c++){
                    m->numbers[r][c] = 0;
                }
            }
            break;
            
        case 1:
            
            for(int r = 0; r < 4; r++){
                for(int c = 0; c < 4; c++){
                    if(r == c){ m->numbers[r][c] = 1;}
                    else{ m->numbers[r][c] = 0; }
                }
            }
            
            break;
    }
}

/* scale, rotate, translate: the best order when applying these things. */

void translate(Mat4 *m, Vec3 *v){
    
    Mat4 trans;
    setMat4(&trans, IDENTITY);                      //Turns empty Matrix into Identity matrix
    
    for(int i = 0; i < 3; i++){
        trans.numbers[i][3] += v->verticies[i];     //Then modifies trans to a translation matrix
    }
    
    //This is to determine if the matrix has had anything done to it yet.  If it hasn't then we only need
    //to populate the matrix with the resulting matrix.  If it has had something done to it, then we need to
    //multiply both matricies to combine the translations.
    
    if(m->numbers[0][0] == 0.0f){
        Mat4CopyMat4(m, &trans);
    }
    else{ Mat4XMat4(m, &trans); }                    //Multiply both matricies together for new matrix
    
}

void scale(Mat4 *m, Vec3 *v){
    for(int i = 0; i < 3; i++){
        m->numbers[i][i] = m->numbers[i][i] * v->verticies[i];
    }
}

void rotate(Mat4 *m, float degrees, Vec3 *v){
    
    float Rx = v->verticies[0];
    float Rx2 = v->verticies[0] * v->verticies[0];
    
    float Ry = v->verticies[1];
    float Ry2 = v->verticies[1] * v->verticies[1];
    
    float Rz = v->verticies[2];
    float Rz2 = v->verticies[2] * v->verticies[2];
    
    float RxRy = Rx * Ry;
    float RxRz = Rx * Rz;
    float RyRz = Ry * Rz;
    
    float cos = cosf(degrees);
    float sin = sinf(degrees);
    
    m->numbers[0][0] = cos + (Rx2 - Rx2 * cos);
    m->numbers[1][0] = (RxRy - RxRy * cos) +  Rz * sin;
    m->numbers[2][0] = (RxRz - RxRz * cos) +  Ry * sin;
    //Do nothing with [3][0]
    
    m->numbers[0][1] = (RxRy - RxRy * cos) - Rz * sin;
    m->numbers[1][1] = cos + (Ry2 - Ry2 * cos);
    m->numbers[2][1] = (RyRz - RyRz * cos) + Rx * sin;
    //Do nothing with [3][1]
    
    m->numbers[0][2] = (RxRz - RxRz * cos) + Ry * sin;
    m->numbers[1][2] = (RyRz - RyRz * cos) - Rx * sin;
    m->numbers[2][2] = cos + (Rz2 - Rz2 * cos);
    //Do nothing with [3][2]
    
    //Do nothing with [0][3]
    //Do nothing with [1][3]
    //Do nothing with [2][3]
    //Do nothing with [3][3]
}

void Mat4XVec4(Mat4 *m, Vec4 *v){
    
    Vec4 tempVec;
    for(int i = 0; i < 4; i++){ tempVec.verticies[i] = 0; }
    
    for(int r = 0; r < 4; r++){         // 4 times ->Columns
        for(int c = 0; c < 4; c++){     //16 times ->Rows
            tempVec.verticies[r] += m->numbers[r][c] * v->verticies[c];
        }
    }
    
    for(int i = 0; i < 4; i++){ v->verticies[i] = tempVec.verticies[i]; }
    
}

void Mat4CopyMat4(Mat4 *m1, Mat4 *m2){

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            m1->numbers[i][j] = m2->numbers[i][j];
        }
    }

}

void Mat4XMat4(Mat4 *m1, Mat4 *m2){

    Mat4 result;
    setMat4(&result, EMPTY);
    
    /* 4x4 Matrix Multiplication
                                   n
         m1            m2          |
     [ 1 0 0 0 ]   [ 1 0 0 0 ]   [ 1 0 0 0 ] -|
     [ 0 1 0 0 ] * [ 0 1 0 0 ] = [ 0 1 0 0 ]  | r
     [ 0 0 1 0 ]   [ 0 0 1 0 ]   [ 0 0 1 0 ]  |
     [ 0 0 0 1 ]   [ 0 0 0 1 ]   [ 0 0 0 1 ] -|
                                 |_________|
                                      c
     */
    
    printMat4(m1);
    printMat4(m2);
    
    for(int c = 0; c < 4; c++){             // i
        for(int r = 0; r < 4; r++){         // j
            for(int n = 0; n < 4; n++){     // k
                result.numbers[r][c] += m1->numbers[n][c] * m2->numbers[r][n];
            }
        }
    }
    
    for(int c = 0; c < 4; c++){
        for(int r = 0; r < 4; r++){
            m1->numbers[r][c] = result.numbers[r][c];
        }
    }
}

void printVec4(Vec4 *v){
    
    printf(" %.1f, %.1f, %.1f, %.1f \n\n", v->verticies[0], v->verticies[1], v->verticies[2], v->verticies[3]);
    
}

void printMat4(Mat4 *m){
    
    for(int r = 0; r < 4; r++){         // 4 times ->Columns
        for(int c = 0; c < 4; c++){     //16 times ->Rows
            printf(" %.1f, ", m->numbers[r][c]);
        }
        printf("\n");
    }
    printf("\n");
    
}


#endif /* MyGLM_h */
