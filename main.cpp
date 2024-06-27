#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

ShaderProgram* shaderProgram;

/**
 * Main loop of the program, used for anything that needs to be called each frame.
 */
void mainLoop()
{
	while (!glfwWindowShouldClose(shaderProgram->window)) 
	{
		shaderProgram->draw();
		
		glfwPollEvents();
	}
}

int main(int argc, char* argv[]) 
{
	// Checks .obj file given
	if (argc <= 1)
	{
		std::cout << "You Must Input A File Path For A (.OBJ) File.\n";
		return 0;
	}

	// Create Shader Program
	shaderProgram = new ShaderProgram(argv[1]);
	if (!shaderProgram->validMesh)
	{
		std::cout << "Mesh File Or Path To Mesh File Wasn't Valid.\n";
		return 0;
	}
	
	if (!shaderProgram->initialize())
	{
		std::cout << "Failed To Initialize Shader Program.\n";
		return 0;
	}
	
	mainLoop();
	
	shaderProgram->closeProgram();
	glfwTerminate();

	return 0;
}