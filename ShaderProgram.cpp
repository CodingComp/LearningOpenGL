#include "ShaderProgram.h"

// Loads a .obj mesh from a file path
ShaderProgram::ShaderProgram(char const* filePath)
{
	mesh = new cy::TriMesh;
	validMesh = mesh->LoadFromFileObj(filePath);

	projectionMatrix = cy::Matrix4f::Identity();
	projectionMatrix.SetDiagonal(0.05f, 0.05f, 0.05f);
	/*
	projectionMatrix = cy::Matrix4f::Perspective(
		float(40 * (atan(1)*4) / 180.0), float(width)/float(height), 0.1f, 1000.0f);
		*/

	cells = new float[16];
	projectionMatrix.Get(cells);
	/* // Prints matrix cells array
	 for (int row = 0; row < 4; row++)
	{
		std::cout << cells[row + (row * 3)] << " " << cells[row + (row * 3) + 1]  << " " <<cells[row + (row * 3) + 2] << " " << cells[row + (row * 3) + 3] << "\n";
	}
	*/
}


// Reads shader code from the shader.vert & shader.frag
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

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		std::cout<<"Change Perspective.\n";
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
	vbo = new VBO(&mesh->V(0), sizeof(cy::Vec3f) * mesh->NV());
 	
	// Links VBO attributes
	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(cy::Vec3f), 0);
	
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
	
	shaderProgram.Bind();
	
	shaderProgram.SetUniformMatrix4("mvp", cells);

	vao->Bind();
	
	glDrawArrays(GL_POINTS, 0, mesh->NV());
	
	glfwSwapBuffers(window);
}


void ShaderProgram::closeProgram()
{
	glfwDestroyWindow(window);
}


void ShaderProgram::recompileShaders()
{
	
}


void ShaderProgram::changePerspective()
{
	
}
