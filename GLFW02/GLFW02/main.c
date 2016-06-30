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
#include <math.h>

/*
const GLchar* vertexShaderSource = "#version 330 core\n "
    "layout (location = 0) in vec3 position; \n "
    "layout (location = 1) in vec3 color; \n"
    "out vec3 ourColor; \n"
    "void main()\n "
    "{\n "
    "gl_Position = vec4(position, 1.0); \n"
    "ourColor = color; \n"
    "}\0";
*/
 
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "in vec3 ourColor; \n"
    "out vec4 color;\n "
    "void main()\n "
    "{\n "
    "color = vec4(ourColor, 1.0f);\n "
    "}\n\0";

const GLchar* vertexShaderSourceFromFile = "";

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode){

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    }

}

int main(int argc, const char * argv[]) {
    
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
    
    FILE *file;
    char c;
    int i = 0;
    char vertexShaderString[183];
    
    file = fopen("/Users/alexregister/Documents/Git/OpenGL/GLFW02/GLFW02/vShader.txt", "r");
    
    if(file){
        while((c = fgetc(file))!=EOF){
            //printf("%c", c);
            vertexShaderString[i] = c;
            i++;
        }
    }
    else{
        perror("OH NO!!!");
    }
    
    //printf("%s", vertexShaderString);
    
    fclose(file);
    
    const GLchar* vertexShaderSource = vertexShaderString;
    //printf("%s", vertexShaderString);
    //printf("%s", vertexShaderSource);

    //Need FILE converted to const GLuint!!!
    
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
    
    /* How to check for compile time errors:
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR:SHADER:FRAGMENT:COMPILATION_FAILED\n");
    } */
    
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    /* How to check for Linking errors:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if(!suceess){
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR:SHADER:PROGRAM:LINKINGFAILED\n");
    }
     */
    
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //Actually making the triangle
    GLfloat vertices[] = {
         //Positions         //Colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //Bottom Left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   //Top

    };
    
    GLuint VBO, VAO; //Stands for Vertex Buffer Object, and Vertex Array Object
    glGenBuffers(1, &VBO); //Generates Buffer
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binds VBO to Array buffer, can bind VBO to multiple buffers, only do it once per VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //copies array Vertices into buffer's memory.
    
    //Possition attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
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
