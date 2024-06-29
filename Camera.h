#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera
{
	bool orthographicPerspective = false;
	bool mousePressed = false;
	bool lockCursor = true;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	int width, height;

	GLuint shaderID;

	GLint matrixLoc;

	glm::mat4 view, projection;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);

public:
	// Projection Matrix Vars
	float mTop = 20.0f;
	float mBottom = -20.0f;

	float mRight = 20.0f;
	float mLeft = -20.0f;

	float mFar = 1000.0f;
	float mNear = 0.1f;

	float fov = 80.0f;

	/**
	 * 
	 * @param shaderID ID used for 
	 * @param width 
	 * @param height 
	 */
	Camera(GLuint shaderID, int width, int height);

	/**
	 * Calculates the cameraMatrix to be used in the vertex shader.
	 */
	void matrix();

	/**
	 * Toggles perspective state. Toggling to either perspective or orthographic projection.
	 */
	void changePerspective();

	/**
	 * Handles inputs that the camera uses. Such as moving camera position & camera viewing angles.
	 * @param window OpenGL window pointer.
	 */
	void inputs(GLFWwindow* window);

};
