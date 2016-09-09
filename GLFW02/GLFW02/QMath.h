//
//  QMath.h
//  GLFW02
//
//  Created by Alex Register on 7/15/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef QMath_h
#define QMath_h

#include <math.h>

typedef struct Vector3{
    float x, y, z;
} Vec3;

typedef struct Vector4{
    float x, y, z, w;
} Vec4;

typedef struct VectorArray4{
    float val[4];
} VecArr4;

void setVec3(Vec3 *v, float x, float y, float z);
void setVec4(Vec4 *v, float x, float y, float z, float w);
void qVectorToUnitVector(Vec3 *u, Vec4 *v);
void qVectorToUnitQuaternion(Vec4 *q, Vec4 *v);
void qPointToQuaternion(Vec4 *q, Vec3 *p);
void qDegreesToRadians(float *f, float *d);
void qMultiply(Vec4 *q3, Vec4 *q1, Vec4 *q2);
void qRotate(Vec3 *p, Vec4 *v, Vec3 *rp);

void setVec2(Vec3 *v, float x, float y){
    v->x = x;
    v->y = y;
}

void setVec3(Vec3 *v, float x, float y, float z){
    v->x = x;
    v->y = y;
    v->z = z;
}

/* 
assigns values to given Vec4
 
@param v - The vector to assign values to
@param x - the x-component
 
@return the vec4 with the new values

 */
void setVec4(Vec4 *v, float x, float y, float z, float w){
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

void qVectorToUnitVector(Vec3 *u, Vec4 *v){
    
    /* Takes a Vec4 Vector, Returns a Vec3 Unit Vector, separates the Vector from angle of rotation. */
    
    float vMag = sqrtf( powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2)); //Vector's Magnitude
    float vLength = vMag / powf(vMag, 2);                               //Vectors Length
    
    u->x = v->x * vLength;                                              //Unit Vector x, y, and z.
    u->y = v->y * vLength;
    u->z = v->z * vLength;
    
}





void qVectorToUnitQuaternion(Vec4 *q, Vec4 *v){

    //quaternion definition = (Cos(ø/2) + (Uvx * Sin(ø/2))i + (Uvy * Sin(ø/2))j + (Uvz * Sin(ø/2))k)
    //where the axis of rotation = (Uvx, Uvy, Uvz)
    
    Vec3 u;
    float radiansTheta;
    
    qVectorToUnitVector(&u, v);
    
    qDegreesToRadians(&radiansTheta, &v->w);
    
    float half_sine = sinf(radiansTheta / 2);
    
    setVec4(q, u.x * half_sine, u.y * half_sine, u.z * half_sine, cosf(radiansTheta / 2));

}





void qPointToQuaternion(Vec4 *q, Vec3 *p){ setVec4(q, p->x, p->y, p->z, 0); }

void qDegreesToRadians(float *r, float *d){ *r = *d * 3.14159 / 180; }

void qMultiply(Vec4 *q3, Vec4 *q1, Vec4 *q2){
    
    //Q1 x Q2 = (w1 * w2 - dot(V1, V2), w1 * V2 + w2 * V1 + cross(V1 * V2));
    
    q3->w = q1->w * q2->w - q1->x * q2->x + q1->y * q2->y + q1->z * q2->z;
    q3->x = q1->w * q2->x + q2->w * q1->x + q1->y * q2->z - q1->z * q2->y;
    q3->y = q1->w * q2->y + q2->w * q1->y + q1->z * q2->x - q1->x * q2->z;
    q3->z = q1->w * q2->z + q2->w * q1->z + q1->x * q2->y - q1->y * q2->x;
    

}

void qRotate(Vec3 *p, Vec4 *v, Vec3 *rp){
    
    /* Rotates */
    
    //p' = q1 * q2 * conjucate(q1).
    
    Vec4 q1, q2, halfRotation, fullRotation; //Quaternions
    
    qVectorToUnitQuaternion(&q1, v);
    
    qPointToQuaternion(&q2, p);
    
    qMultiply(&halfRotation, &q1, &q2);
    
    setVec4(&q1, -q1.x, -q1.y, -q1.z, q1.w); //Conjugate of q1
    
    qMultiply(&fullRotation, &halfRotation, &q1);
    
    setVec3(rp, fullRotation.x, fullRotation.y, fullRotation.z);
    
}

#endif /* QMath_h */
