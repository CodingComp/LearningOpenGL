#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include <glm/mat4x4.hpp> // glm::mat4
#include<glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

class Model 
{
    // model data
    std::string directory;

    // Matrix Models
    glm::mat4 m_Position = glm::mat4(1.0f);
    glm::mat4 m_Rotation = glm::mat4(1.0f);
    glm::mat4 m_Scale = glm::mat4(1.0f);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    void updateMatrix();
    
public:
    Model() { }

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::mat4 m;
    
    std::vector<Mesh> meshes;

    bool loadModel(std::string filepath);
    
    /**
     * Sets a new position of the model.
     * @param pos New position of model.
     */
    void move(glm::vec3 pos);

    /**
     * Sets a new rotation of the model.
     * @param rot New rotation of model.
     */
    void rotate(glm::vec3 rot);

    void Draw();
};