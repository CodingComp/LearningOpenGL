#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

ShaderProgram* shaderProgram;

// Main loop of the program, used for anything that needs to be called each frame.
void mainLoop()
{
	while (!glfwWindowShouldClose(shaderProgram->window)) 
	{
		shaderProgram->draw();
		
		glfwPollEvents();
	}
}


int main() 
{
	shaderProgram = new ShaderProgram();
	
	if (!shaderProgram->initialize()) return -1;
	
	mainLoop();
	
	shaderProgram->closeProgram();
	glfwTerminate();

	return 0;
}