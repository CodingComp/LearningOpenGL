#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(char const* filePath)
{
	mesh = new cy::TriMesh;
	validMesh = mesh->LoadFromFileObj(filePath);
	if (!validMesh) return;
	
	// Rotates teapot
	model = rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))*
			rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
			rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate teapot
	view = translate(view, glm::vec3(0.0f, -10.0f, -30.0f));
	
	m = view * model;
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

bool ShaderProgram::initialize()
{
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

	// Sets key callack for GLFW. Sets pointer to this shader class to be used in the callback function
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
		// Retrieve class ptr
		ShaderProgram* program = static_cast<ShaderProgram*>(glfwGetWindowUserPointer(win));
	            
		// Call member function
		if (program) 
			program->keyCallback(win, key, scancode, action, mods);
	});

	// Moves cursor to center before draw to avoid camera jult
	glfwSetCursorPos(window, width/2, height/2); 
	
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	CY_GL_REGISTER_DEBUG_CALLBACK
	
	/*
	 *	Shaders
	 */
	
	compileShaders();
	
	vao = new VAO();
	vao->Bind();
	
	vbo = new VBO(&mesh->V(0), sizeof(cy::Vec3f) * mesh->NV());
	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(cy::Vec3f), 0);
	
	vao->Unbind();
	vbo->Unbind();
	
	camera = new Camera(shaderProgram.GetID(), width, height);

	prevTime = glfwGetTime();
	
	return true;
}

void ShaderProgram::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	shaderProgram.Bind();

	double time = glfwGetTime();
	if (time - prevTime >= 1 / 60)
	{
		modelRotation += 0.5f;
		prevTime = time;
	}
	
	// Rotates teapot
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);

	// Rotates the model on the Z axis
	model = rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
			rotate(model, glm::radians(modelRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	view = translate(view, glm::vec3(0.0f, -10.0f, -30.0f));

	m = view * model;
	
	camera->inputs(window);
	camera->matrix();

	shaderProgram.SetUniformMatrix4("objectMatrix", value_ptr(m));
	vao->Bind();

	glDrawArrays(GL_POINTS, 0, mesh->NV());
	glfwSwapBuffers(window);
}

void ShaderProgram::closeProgram()
{
	glfwDestroyWindow(window);
}

void ShaderProgram::compileShaders()
{
	shaderProgram.BuildFiles("shader.vert", "shader.frag");
	shaderProgram.Link();
}

void ShaderProgram::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS) // Change Perspective
		camera->changePerspective();

	if (key == GLFW_KEY_F6 && action == GLFW_PRESS) // Recompile Shaders
		compileShaders();
}
