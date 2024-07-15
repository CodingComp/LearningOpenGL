#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Vertex.h"

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

class Mesh
{
    void setupMesh();
    
public:
    
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void Draw();
};
