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
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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

    // Vertex Shader Matrix
    glm::mat4 m;

    // Matrix Models
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    
    // Projection Matrix Vars
    float mTop =  20.0f;
    float mBot = -20.0f;

    float mRight = 20.0f;
    float mLeft = -20.0f;
    
    float mFar = 1000.0f;
    float mNear = 0.1f;

    bool orthoPerspective;
    
public:
    GLFWwindow* window;

    bool validMesh = false;
    
    // Loads a .obj mesh from a file path
    ShaderProgram(char const* filePath);
    
    bool initialize();
    
    void draw();

    void closeProgram();

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void recompileShaders();
};
