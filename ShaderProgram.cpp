#include "ShaderProgram.h"

// 3f: Position | 3f: Color
GLfloat positions[] =
{
	-0.5f, -0.5f * float(sqrt(3))     / 3, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f * float(sqrt(3))     / 3, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.0f, 0.0f,
};


ShaderProgram::ShaderProgram()
{
	
}


const char* ShaderProgram::readShaderCode(const char* fileName)
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
void ShaderProgram::keyCallback(GLFWwindow* windowRef, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(windowRef, GLFW_TRUE);
}


// Initializes GLFW & OpenGL. If initialization fails this function returns false.
bool ShaderProgram::initialize()
{
	// Initialize GLFW
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	
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

	CY_GL_REGISTER_DEBUG_CALLBACK
	
	/*
	 *	Shaders
	 */
	
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
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// Generates Vertex Array Object and binds it
	vao = new VAO();
	vao->Bind();
	
	// Generates Vertex Buffer Object and links it to vertices
	vbo = new VBO(positions, sizeof(positions));

	// Links VBO attributes
	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), 0);
	vao->LinkAttribute(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	vao->Unbind();
	vbo->Unbind();
	
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	
	return true;
}


void ShaderProgram::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao->ID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glfwSwapBuffers(window);
}


void ShaderProgram::closeProgram()
{
	glfwDestroyWindow(window);
}
