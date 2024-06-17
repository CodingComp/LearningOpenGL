#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int width = 1920;
int height = 1080;


// Callback function for when a key is pressed.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


// Main loop of the program, used for anything that needs to be called each frame.
void mainLoop()
{
	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}
}


// Initializes GLFW & OpenGL. If initialization fails this function returns false.
bool initialize()
{
	// Initialize GLFW
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Create Window
	window = glfwCreateWindow(width, height, "OpenGL Learning", NULL, NULL);
	if (!window) 
	{
		std::cout << "Failed To Create Window\n";
		glfwTerminate();
		return false;
	}
	
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	glfwSetKeyCallback(window, keyCallback);
	
	glClearColor(0.061f,0.096f,0.121f,1.0f);
	
	return true;
}


int main() 
{
	if (!initialize()) return -1;
	
	mainLoop();
	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}