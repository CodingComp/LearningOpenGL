#pragma once

#include <iostream>
#include <list>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cy/cyGL.h>
#include <glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"
#include "Camera.h"
#include "Model.h"

class ShaderProgram
{
	int height = 1200;
	int width = 1200;

	VBO* vbo;
	VAO* vao;

	Camera* camera;

	// Reads shader code from the shader.vert & shader.frag
	const char* readShaderCode(const char* fileName);

	cy::GLSLProgram shaderProgram;

	// Vertex Shader Matrix
	glm::mat4 m;

	// Matrix Models
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Model Rotation Variables
	float modelRotation = 0.0f;
	double prevTime;

	// List of models to be drawn
	std::vector<Model*> models;
	
public:
	GLFWwindow* window;

	/**
	 * Initializes ShaderProgram
	 */
	ShaderProgram();

	/**
	 * Initializes the ShaderProgram. Sets variables needed for OpenGL.
	 * @return If the shaderProgram successfully initialized or not.
	 */
	bool initialize();

	/**
	 * Draws data to the screen.
	 */
	void draw();

	/**
	 * Creates a new model object to be drawn.
	 * @param filepath Filepath to a .OBJ model file.
	 */
	void addModel(const char* filepath);

	/**
	 * Properly closes the program.
	 */
	void closeProgram();

	/**
	 * Compiles shaders to be used in OpenGL.
	 */
	void compileShaders();

	/**
	 * Callback used for when an input is registered by GLFW.
	 * @param window Reference to OpenGL window.
	 * @param key Key code of key pressed.
	 * @param scancode Unique code for key pressed.
	 * @param action Type of input given.
	 * @param mods Modifiers to key inputs. (Shift + KEY , Ctrl + KEY, etc.)
	 */
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
