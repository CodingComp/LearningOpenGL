#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"
#include "VAO.h"

class ShaderProgram
{
    int width = 800;
    int height = 800;

    GLuint program;

    VBO* vbo;
    VAO* vao;

    const char* readShaderCode(const char* fileName);

    // Callback function for when a key is pressed.
    static void keyCallback(GLFWwindow* windowRef, int key, int scancode, int action, int mods);
    
public:
    GLFWwindow* window;

    ShaderProgram();
    
    bool initialize();
    
    void draw();

    void closeProgram();
};
