//
//  main.c
//  GLFW02
//
//  Created by Alex Register on 4/7/16.
//  Copyright © 2016 Alex Register. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#include <math.h>
#include "SOIL.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

const int bufferSize = 512;

int main(int argc, const char * argv[]) {
    
    struct Vec3 transVector;
    newVec3(&transVector, 1.0f, 1.0f, 0.0f);
    
    struct Vec4 vector;
    newVec4(&vector, 1.0f, 0.0f, 0.0f, 1.0f);
    
    struct Mat4 trans;
    mat4Identity(&trans); //Identity Matrix by default
    
    printMat4(&trans);
    
    mat4Translate(&trans, &transVector);
    
    printMat4(&trans);
    
    multiply(&trans, &vector);
    
    printVec4(&vector);
    
    
    glfwInit();
    
    //glfwWindowHint "tells us what option we want to configure".  (Option to change, value)
    //See: http://www.glfw.org/docs/latest/window.html for more options to set using glfwWindowHint.
    
    //Source code: http://www.learnopengl.com/code_viewer.php?code=getting-started/hellotriangle
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Needed for OSX
    
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    
    if(window == NULL){ //This check is not in the source code
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    /* GLEW: *shouldnt need this code*
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        printf("Failed to initialize GLEW");
        return -1;
    }
     */
    glfwSetKeyCallback(window, key_callback);
    
    glViewport(0, 0, 800, 600);
    
    FILE *vertexFile, *fragmentFile;
    char c;
    char vertexShaderString[bufferSize] = {'\0'};
    char fragmentShaderString[bufferSize] = {'\0'};
    
    vertexFile = fopen("Shaders/vShader.txt", "r");
    fragmentFile = fopen("Shaders/fShader.txt", "r");
    
    /*
     Dont put '\0' at end of any shader file.  
     
     ERROR: 0:11: '<' : syntax error: syntax error
     
     Escape (\) characters are not supported in the GLSL compiler.
    */
    
    if(vertexFile){
        int i;
        for(i = 0; (c = fgetc(vertexFile)) != EOF && i < bufferSize - 1 ; i++){ vertexShaderString[i] = c; }
        vertexShaderString[i] = '\0';
    } else { perror("OH NO!!!"); }
    
    if(fragmentFile){
        int i;
        for(i = 0; (c = fgetc(fragmentFile)) != EOF && i < bufferSize - 1; i++){ fragmentShaderString[i] = c; }
        fragmentShaderString[i] = '\0';
    } else { perror("OH NO!!!"); }
    
    
    fclose(fragmentFile);
    fclose(vertexFile);
    
    const GLchar* vertexShaderSource = vertexShaderString;
    const GLchar* fragmentShaderSource = fragmentShaderString;
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf(" ERROR:SHADER:VERTEX:COMPILATION_FAILED\n %s", infoLog);
    }
    
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    /* How to check for compile time errors: */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf(" ERROR:SHADER:VERTEX:COMPILATION_FAILED\n %s", infoLog);
    }
    
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    /* How to check for Linking errors:*/
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf(" ERROR:SHADER:VERTEX:COMPILATION_FAILED\n %s", infoLog);
    }
    
    
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //Actually making the triangle
    GLfloat vertices[] = {
         //Positions         //Colors           //Texture
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  //Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //Bottom Left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f   //Top

    };
    
    /* GL texture wrapping options:
     GL_REPEAT (default if none specified)
     GL_MIRRORED_REPEAT: repeats but img is mirrored
     GL_CLAMP_TO_EDGE:  "Clamps" coordinates between 0 and 1.  The result is that higher
                        coordinates become clamped to the edge, resulting in a stretched pattern.
     GL_CLAMP_TO_BORDER: Coordinates outside the range are not given user-specified border color.
     */
    
    /* GL Mipmap filtering methods
        (Mipmaps are used by openGL when high-resolution textures are far away.  When called, 
        it will create the same texture, but twice as small, so that when picking a color for 
        sampling, it is easier and faster).
     
     GL_NEAREST_MIPMAP_NEAREST: Takes the nearest mipmap to match the pixel size and uses nearest
                                neighbor interpolation for texture sampling.
     GL_LINEAR_MIPMAP_NEAREST:  Takes the nearest mipmap level and samples using linear interpolation
     GL_NEAREST_MIPMAP_LINEAR:  Linearly interpolates between the two mipmaps that most closely
                                match the size of a pixel and samples via nearest neighbor interpolation
     GL_LINEAR_MIPMAP_LINEAR:   Linearly interpolates between the two closest mipmaps and samples
                                the texture via linear interpolation.
     */
    
    GLuint VBO, VAO, tex; //Stands for Vertex Buffer Object, and Vertex Array Object
    glGenBuffers(1, &VBO); //Generates Buffer
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binds VBO to Array buffer, can bind VBO to multiple buffers, only do it once per VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies array Vertices into buffer's memory.
    
    //Possition attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //Texture configuration, generation, and binding
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height;
    unsigned char* image = SOIL_load_image("Shaders/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(0);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); //unbind when finished
    
    
    
    //Fourth paramerter indicates what kind of memory data should be stored in:
    //GL_STATIC_DRAW: data will most likely not change at all or rarely.
    //GL_DYNAMIC_DRAW: data is likely to change a lot.
    //GL_STREAM_DRAW: data will change every time it is drawn.
    
    while(!glfwWindowShouldClose(window)){
    
        glfwPollEvents();
        
        //In rendering there are multiple buffers: color, depth, stencil.
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); //if glGetUniformLocation returns -1, "ourColor"
                                                                                     //was not found.
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(glGetUniformLocation(shaderProgram, "sampler"), 0);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    
    
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        
        glfwSetWindowShouldClose(window, GL_TRUE);
        
    }
    
}
