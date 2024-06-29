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
	while(!glfwWindowShouldClose(shaderProgram->window)) {
		shaderProgram->draw();

		glfwPollEvents();
	}
}

int main(int argc, char* argv[])
{
	// Checks .obj file given
	if(argc <= 1) {
		std::cout << "You Must Input A File Path For A (.OBJ) File.\n";
		return 0;
	}

	shaderProgram = new ShaderProgram();

	// Makes sure shaderProgram initialized properly
	if(!shaderProgram->initialize()) {
		std::cout << "Failed To Initialize Shader Program.\n";
		return 0;
	}

	// Adds models passed into program (argv)
	for(int i = 1; i < argc; i++) {
		shaderProgram->addModel(argv[i]);
	}

	mainLoop();

	shaderProgram->closeProgram();
	glfwTerminate();

	return 0;
}
