#pragma once

#include <glad/glad.h>

class VBO
{
public:
    // ID reference for the Vertex Buffer Object
    GLuint ID;
    // Constructor that generates a VBO ID
    VBO(GLfloat* vertices, GLsizeiptr size);

    void Bind();

    void Unbind();

    void Delete();
};
