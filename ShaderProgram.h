#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cy/cyGL.h>
#include <cy/cyTriMesh.h>

#include "VBO.h"
#include "VAO.h"

class ShaderProgram
{
    int width = 800;
    int height = 800;

    VBO* vbo;
    VAO* vao;
    
    const char* readShaderCode(const char* fileName);

    cy::GLSLProgram shaderProgram;
    cy::TriMesh* mesh;

    GLfloat* buffer;
    int bufferByteSize = 0;
    
    // Callback function for when a key is pressed.
    static void keyCallback(GLFWwindow* windowRef, int key, int scancode, int action, int mods);
    
public:
    GLFWwindow* window;

    bool validMesh = false;
    
    ShaderProgram(char const* filePath);
    
    bool initialize();
    
    void draw();

    void closeProgram();
};
