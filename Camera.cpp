#include "Camera.h"
#include <iostream>

Camera::Camera(GLuint shaderID, int width, int height) : width(width), height(height), shaderID(shaderID)
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	matrixLoc = glGetUniformLocation(shaderID, "cameraMatrix");
}

void Camera::matrix()
{
	// Translate Camera
	view = lookAt(position, position + orientation, up);

	// Projection
	projection = orthographicPerspective ?
		glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar) :
		glm::perspective(glm::radians(fov), static_cast<float>(width / height), mNear, mFar);

	// Sets cameraMatrix in Vertex Shader
	glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, value_ptr(projection * view));
}

void Camera::changePerspective()
{
	orthographicPerspective = !orthographicPerspective;
}

void Camera::inputs(GLFWwindow* window)
{
	// Forward
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * orientation;

	// Left
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += speed * -normalize(cross(orientation, up));

	// Back
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += speed * -orientation;

	// Right
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += speed * normalize(cross(orientation, up));

	// Up
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position += speed * up;

	// Down
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		position += speed * -up;

	/*
	 * Mouse Inputs
	 */

	if(glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
		double mouseX, mouseY;
		float rotX, rotY;

		// Rotates camera from mouse movement
		if(lockCursor && !mousePressed) {
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates
			rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			rotY = sensitivity * static_cast<float>(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = rotate(orientation, glm::radians(-rotX), normalize(cross(orientation, up)));

			// Clamps vertical camera to 90 deg
			if(abs(angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			// Rotates the Orientation left and right
			orientation = rotate(orientation, glm::radians(-rotY), up);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwSetCursorPos(window, width / 2, height / 2);
		}

		// Left or Right Mouse Button (Adjust Camera Distance Z Axis)
		if(mousePressed) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			lockCursor = true;

			glfwGetCursorPos(window, &mouseX, &mouseY);

			rotX = sensitivity * static_cast<float>(mouseY - (height / 2)) / height;
			position += rotX * -orientation;
		}
	}

	// Unfocus - When the Esc or ALT key is pressed (ALT for ALT-TAB window change)
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		lockCursor = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	mousePressed =
		glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
		glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

	if(mousePressed) glfwSetCursorPos(window, width / 2, height / 2);
}
