#include "ShaderProgram.h"


void ShaderProgram::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		orthoPerspective = !orthoPerspective;

	if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
		recompileShaders();
}

// Loads a .obj mesh from a file path
ShaderProgram::ShaderProgram(char const* filePath)
{
	mesh = new cy::TriMesh;
	validMesh = mesh->LoadFromFileObj(filePath);
	
	// Rotates teapot
	model = rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f))*
			rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate teapot
	view = translate(view, glm::vec3(-2.0f, -5.0f, -30.0f));

	// Projection 
	proj = glm::perspective(glm::radians(80.0f), (float)(width / height), mNear, mFar);
	
	m = proj * view * model;
	orthoPerspective = false;

	// Prints matrix cells array
	std::cout << m[0][0] << " " << m[1][0] << " " << m[2][0]  << " " << m[3][0] << " \n";
	std::cout << m[0][1] << " " << m[1][1] << " " << m[2][1]  << " " << m[3][1] << " \n";
	std::cout << m[0][2] << " " << m[1][2] << " " << m[2][2]  << " " << m[3][2] << " \n";
	std::cout << m[0][3] << " " << m[1][3] << " " << m[2][3]  << " " << m[3][3] << " \n";
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

	// Stores ptr to this class
	glfwSetWindowUserPointer(window, this);
	//glfwSetKeyCallback(window, key_callback);

	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
		// Retrieve class ptr
		ShaderProgram* program = static_cast<ShaderProgram*>(glfwGetWindowUserPointer(win));
	            
		// Call member function
		if (program) {
			program->keyCallback(win, key, scancode, action, mods);
		}
	});
	
	
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
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

	glEnable(GL_DEPTH_TEST);
	
	return true;
}


void ShaderProgram::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderProgram.Bind();

	// Matracies 
	proj = orthoPerspective ?
		glm::ortho(mLeft, mRight, mBot, mTop, mNear, mFar) :
		glm::perspective(glm::radians(80.0f), (float)(width / height), mNear, mFar);

	m = proj * view * model;
	
	shaderProgram.SetUniformMatrix4("mvp", (float*)&m);

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
	std::cout << "RECOMPILE SHADERS\n";
}
