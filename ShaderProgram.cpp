#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{

}

const char* ShaderProgram::readShaderCode(const char* fileName)
{
	std::ifstream inputFile(fileName);
	static std::string text;
	std::string line;

	// Checks to see if the text is empty & clears if not empty
	if(!text.empty())
		text.clear();

	while(getline(inputFile, line)) {
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
	window = glfwCreateWindow(width, height, "OpenGL Learning", nullptr, nullptr);
	if(!window) {
		std::cout << "Failed To Create Window\n";
		glfwTerminate();
		return false;
	}

	// Sets key callack for GLFW. Sets pointer to this shader class to be used in the callback function
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
		// Retrieve class ptr
		auto program = static_cast<ShaderProgram*>(glfwGetWindowUserPointer(win));

		// Call member function
		if(program)
			program->keyCallback(win, key, scancode, action, mods);
	});

	// Moves cursor to center before draw to avoid camera jult
	glfwSetCursorPos(window, width / 2, height / 2);

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	CY_GL_REGISTER_DEBUG_CALLBACK

	/*
	 *	Shaders
	 */

	compileShaders();

	camera = new Camera(shaderProgram.GetID(), width, height);

	prevTime = glfwGetTime();

	return true;
}

void ShaderProgram::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.Bind();

	camera->inputs(window);
	camera->matrix();

	// Loops over each model and draws it
	for(int i = 0; i < models.size(); i++) {
		shaderProgram.SetUniformMatrix4("objectMatrix", value_ptr(models[i]->m));
		models[i]->vao->Bind();

		glDrawArrays(GL_POINTS, 0, models[i]->mesh->NV());
	}

	glfwSwapBuffers(window);
}

void ShaderProgram::addModel(const char* filepath)
{
	auto newModel = new ModelObject(filepath);

	// Tries to load mesh from filepath. If invalid file model is not added to models list.
	if(!newModel->initialize()) {
		delete newModel;
		return;
	}

	models.push_back(newModel);

	// Manually change position / rotation of objects.
	switch(models.size()) {
	case 1: // Teapot
		models[0]->move(glm::vec3(0.0f, 0.0f, -30.0f));
		models[0]->rotate(glm::vec3(-90.0f, 0.0f, 0.0f));
		break;
	case 2: // Table
		models[1]->move(glm::vec3(0.0f, -37.5f, -28.25f));
		models[1]->rotate(glm::vec3(0.0f, 0.0f, 0.0f));
		break;
	}
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
	if(key == GLFW_KEY_P && action == GLFW_PRESS) // Change Perspective
		camera->changePerspective();

	if(key == GLFW_KEY_F6 && action == GLFW_PRESS) // Recompile Shaders
		compileShaders();
}
