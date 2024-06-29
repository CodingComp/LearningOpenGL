#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cy/cyGL.h>
#include <cy/cyTriMesh.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include<glm/gtc/type_ptr.hpp>

#include "VAO.h"
#include "VBO.h"

class ModelObject
{
	// Matrix Models
	glm::mat4 m_Position = glm::mat4(1.0f);
	glm::mat4 m_Rotation = glm::mat4(1.0f);
	glm::mat4 m_Scale = glm::mat4(1.0f);

	const char* filepath;

	void updateMatrix();

public:
	cy::TriMesh* mesh;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 m;

	VAO* vao;
	VBO* vbo;

	/**
	 * 
	 * @param filePath Filepath to a .OBJ model file
	 */
	ModelObject(const char* filePath);

	/**
	 * Initializes the model object. 
	 * @return True / False based on if the model was able to initialize.
	 */
	bool initialize();

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
};
