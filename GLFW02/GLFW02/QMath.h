//
//  QMath.h
//  GLFW02
//
//  Created by Alex Register on 7/15/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#ifndef QMath_h
#define QMath_h

#include "MyGLM.h" //Used only for the definition of known GLM types, not used for its math capabilities.

/*

 This method will be a test method for rotating a point on a vector using quaternions.
 At first, it makes sense to take in a point, a vector and a rotational value in degrees (or radians depending 
 on which is better).
 
 So something like: 
 
    qMath(Vec3 *P, float deg, Vec4 *V){ ... }
 
 So here are the things known that I need to use: 
 
    Getting the Magnitude of Vector:
 
        Vmag = sqrt(V->x^2 + V->y^2 + V->z^2)
 
        Magnitude of Vector equals the square root of the sum of the vector's x, y, and z values 
        all to the 2nd power.  The Magnitude Vector is used to aid getting the Unit vector.
 
    Getting the Unit Vector:
 
        Uv = 1 / Vmag x (V->x, V->y, V->z)
 
        Unit Vector equals 1 over Vmag multiplied by all values of V.  Outcome should be another Vec3 type.
        Unit Vector is a Vector with each axis containing a magnitude of 1.  The point to having all
        the axis' having a magnitude of 1 is so that only rotation happens to the points.  Any result
        outside of the number 1 or 0 is unknown (1 being strictly rotation, 0 being no rotation about the 
        coresponding axis).
 
    Getting the Quaternion Vector:
 
        Qv = cosf(deg / 2) + (Uv.x * sinf(deg / 2))i + (Uv.y * sin(deg / 2))j + (Uv.z * sin(deg/2))k 
 
        The Quaterian Vector is derived by this magical thingy that I don't know how it works!  The Quanternion 
        Vector is a 4 dimensional imaginery complex number that calculates (to some degree) the angle of 
        rotation using all three axis and angle of rotation as inputs.
 
        - Optimization - Optimized to make shorter (not more readable)
 
        s = sinf(deg / 2)
        c = cosf(deg / 2)
        Qv = c + (Uv.x * s)i + (Uv.y * s)j + (Uv.z * s)k
 
        * this is not going to be a simple plug-n-go scenario as the resulting i, j, and k values will be next to
            the new numbers (i = x, j = y, k = z).  So keeping all these numbers separate will be important.
 
        Qv = c + (Uvxs)i + (Uvys)j + (Uvzs)k
 
    Getting the Quanternion Point:
 
        Qp = w +xi + yj + zk
 
        Quaternion Point is to convert the point to be rotated about the Vector, into quanternian form so
        calculations can be made on that point.  w is normally 0 with its x, y, and z variables as the point's
        x, y and z values.
 
    Getting the rotated point:
 
        Rp = Qv * p * Qv(conjucate)
 
        Rotated Point equals the Quaternion Vector times the point times the Conjucate of the Quaternion Vector.
        The Rp should be a Vec4 with the new point and the w of that point should be 0.
 
        Qv = c + (Uvxs)i + (Uvys)j + (Uvzs)k        (see above)
        p = w + xi + yj + zk                        (w usually 0, not included in calculation)
        Qvc = c - (Uvxs) - (Uvys)j - (Uvzs)k        (conjucate)
 
        (c + (Uvxs)i + (Uvys)j + (Uvzs)k) * (w + xi + yj + zk) * (c - (Uvxs) - (Uvys)j - (Uvzs)k)
 
        - distribute Qv into p -
 
        (cxi + cyj + czk + (Uvxs * x)i^2 + (Uvxs * y)ij + (Uvxs * z)ik + (Uvys * x)ji + (Uvys * y)j^2 + (Uvys * z)jk + (Uvzs * x)ki + (Uvzs * y)kj + (Uvzs * z)k^2) * (c - (Uvxs)i - (Uvys)j - (Uvzs)k)
 
        - Simplify - (a little)
 
        (cxi + cyi + czk - (Uvxs * x)    + (Uvxs * y)k  - (Uvxs * z)j  - (Uvys * x)k  - (Uvys * y)    + (Uvys * z)i  + (Uvzs * x)j  - (Uvzs * y)i  - (Uvzs * z))    * (c - (Uvxs)i - (Uvys)j - (Uvzs)k)
 
        - distribute Qvp into Qv's conjugate -
    
        
 
    Quanternion identities:
 
        i = sqrt(-1), which has no answer, but i^2 = -1.
 
        i^2 = j^2 = k^2 = ijk = -1
 
        ij =  k, jk =  i, ki =  j
        ji = -k, kj = -i, ik = -j
 
 
 */

void qRotate(Vec4 *P, float deg, Vec3 *V){
    
    /* Not sure if storing variables is better than just going to grab the values every time.  It is helping
     with notation though.  If going to get the number is better, the typedef for both Vec3 and Vec4 can be
     changed to read better whilst doing the math. */
    
    float Px = P->verticies[0];
    float Py = P->verticies[1];
    float Pz = P->verticies[2];
    float Pw = P->verticies[3];
    
    float Vx = V->verticies[0];
    float Vy = V->verticies[1];
    float Vz = V->verticies[2];

    printf("Rotating Point: (%.1f, %.1f, %.1f, %.1f) ", Px, Py, Pz, Pw);
    printf("by %.1f degrees ", deg);
    printf("with a Vector of: (%.1f, %.1f, %.1f) \n", Vx, Vy, Vz);
    
    float Vmag = sqrtf( powf(Vx, 2) + powf(Vy, 2) + powf(Vz, 2));
    
    printf("Vector Magnitude: %.1f \n", Vmag);
    
    float Uvx = Vx * Vmag / powf(Vmag, 2);
    float Uvy = Vy * Vmag / powf(Vmag, 2);
    float Uvz = Vz * Vmag / powf(Vmag, 2);
    
    printf("Unit Vector: (%.1f, %.1f, %.1f) \n", Uvx, Uvy, Uvz);
    
    float Uvmag = sqrtf( powf(Uvx, 2) + powf(Uvy, 2) + powf(Uvz, 2));
    
    printf("Unit Vector Magnitude: %.1f \n", Uvmag);
    
    
}

#endif /* QMath_h */
