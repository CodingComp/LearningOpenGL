#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int width = 800;
int height = 800;

GLuint shaderProgram;

GLuint VBO, VAO;

float positions[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
};

const char* readShaderCode(const char* fileName)
{
	std::ifstream inputFile(fileName);
	static std::string text;
	std::string line;

	// Checks to see if the text is empty & clears if not empty
	if (!text.empty())
		text.clear();
	
	while (getline(inputFile, line))
	{ 
		text += line + '\n';
	} 
	
	inputFile.close();
	
	return text.c_str();
}


// Callback function for when a key is pressed.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glfwSwapBuffers(window);
}


// Main loop of the program, used for anything that needs to be called each frame.
void mainLoop()
{
	while (!glfwWindowShouldClose(window)) 
	{
		draw();
		
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
	
	glClearColor(1.0f,1.0f,1.0f,1.0f);

	/*
	 *	Shaders
	 */
	shaderProgram = glCreateProgram();

	// Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderCode = readShaderCode("shader.vert");
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragShaderCode = readShaderCode("shader.frag");
	glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
	glCompileShader(fragmentShader);

	// Program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// Generate VAO & VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	
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