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

struct Mat4{
    
};

#endif /* Mat4_h */
