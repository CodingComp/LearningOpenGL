#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cy/cyGL.h>
#include <cy/cyTriMesh.h>
#include <cy/cyMatrix.h>
#include <cmath>

#include "VBO.h"
#include "VAO.h"

class ShaderProgram
{
    int width = 800;
    int height = 800;

    VBO* vbo;
    VAO* vao;

    // Reads shader code from the shader.vert & shader.frag
    const char* readShaderCode(const char* fileName);

    cy::GLSLProgram shaderProgram;
    cy::TriMesh* mesh;
    
    // Callback function for when a key is pressed.
    static void keyCallback(GLFWwindow* windowRef, int key, int scancode, int action, int mods);

    float* cells;
    cy::Matrix4f projectionMatrix;
    
public:
    GLFWwindow* window;

    bool validMesh = false;

    // Loads a .obj mesh from a file path
    ShaderProgram(char const* filePath);
    
    bool initialize();
    
    void draw();

    void closeProgram();

    void recompileShaders();

    void changePerspective();
};
