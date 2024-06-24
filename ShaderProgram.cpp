#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(char const* filePath)
{
	mesh = new cy::TriMesh;
	validMesh = mesh->LoadFromFileObj(filePath);

	// Each vertex point's X Y Z (*3) float stored.
	int bufferArraySize = mesh->NV() * 3;
	buffer = new GLfloat[bufferArraySize];
	
	bufferByteSize = bufferArraySize * sizeof(float);

	// Loops over each vertex and stores X Y Z floats into buffer.
	int bufferIndex = 0;
	for (int i = 0; i < mesh->NV(); i++)
	{
		cy::Vec3f pos = mesh->V(i);
		
		buffer[bufferIndex]   = pos.x;
		buffer[bufferIndex+1] = pos.y;
		buffer[bufferIndex+2] = pos.z;

		bufferIndex += 3;
	}
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
	
	shaderProgram.BuildFiles("shader.vert", "shader.frag");
	shaderProgram.Link();
	
	// Generates Vertex Array Object and binds it
	vao = new VAO();
	vao->Bind();
	
	// Generates Vertex Buffer Object and links it to vertices
	vbo = new VBO(buffer, bufferByteSize);

	// Links VBO attributes
	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	
	// Unbind all to prevent accidentally modifying them
	vao->Unbind();
	vbo->Unbind();
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	
	return true;
}


void ShaderProgram::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram.GetID());
	glBindVertexArray(vao->ID);
	glDrawArrays(GL_POINTS, 0, mesh->NV());
	
	glfwSwapBuffers(window);
}


void ShaderProgram::closeProgram()
{
	glfwDestroyWindow(window);
}
