#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    setupMesh();
}

void Mesh::setupMesh()
{
    vao = new VAO();
    vao->Bind();
	
    vbo = new VBO(&vertices[0], vertices.size() * sizeof(Vertex));
    ebo = new EBO(&indices[0], indices.size() * sizeof(unsigned int));
    
    vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao->LinkAttribute(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

void Mesh::Draw()
{
    vao->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
