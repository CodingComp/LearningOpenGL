#include "Camera.h"

#include <iostream>


Camera::Camera(int width, int height, GLuint shaderID, float left, float right, float bottom, float top, float near, float far, float fov) :
    width(width), height(height), shaderID(shaderID), _left(left), _right(right), _bottom(bottom), _top(top), _near(near), _far(far), fov(fov)
{
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    matrixLoc = glGetUniformLocation(shaderID, "cameraMatrix");
}


void Camera::matrix()
{
    // Translate Camera
    view = glm::lookAt(position, position + orientation, up);

    // Projection
    projection = orthographicPerspective ?
        glm::ortho(_left, _right, _bottom, _top, _near, _far) :
        glm::perspective(glm::radians(fov), (float)(width / height), _near, _far);
    
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * orientation;

    // Left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position += speed * -glm::normalize(glm::cross(orientation, up));

    // Back
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position += speed * -orientation;

    // Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += speed * glm::normalize(glm::cross(orientation, up));

    // Up
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += speed * up;

    // Down
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position += speed * -up;

    /*
     * Mouse Inputs
     */

    if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
        double mouseX, mouseY;
        float rotX, rotY;

        // Rotates camera from mouse movement
        if (lockCursor && !mousePressed)
        {
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates
            rotX = sensitivity * (float)(mouseY - (height/2)) / height;
            rotY = sensitivity * (float)(mouseX - (width/2)) / width;
            
            glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));
        
            // Clamps vertical camera to 90 deg
            if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            orientation = glm::rotate(orientation, glm::radians(-rotY), up);
            
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            glfwSetCursorPos(window, width/2, height/2);   
        }

        /*
         *  Left & Right Mouse Button
         */
        
        // Left Mouse Button (Adjust Camera Distance Horizontal)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            lockCursor = true;
            
            glfwGetCursorPos(window, &mouseX, &mouseY);
            
            rotY = sensitivity * (float)(mouseX - (width/2)) / width;
            position += rotY * glm::normalize(glm::cross(orientation, up));
        }
        
        // Right Mouse Button (Adjust Camera Distance Vertical)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            lockCursor = true;
            
            glfwGetCursorPos(window, &mouseX, &mouseY);
            
            rotX = sensitivity * (float)(mouseY - (height/2)) / height;
            position += rotX * -orientation;
        }
    }

    // Unfocus - When the Esc or ALT key is pressed (ALT for ALT-TAB window change)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        lockCursor = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (lockCursor)
    {
        mousePressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
               glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

        if (mousePressed) glfwSetCursorPos(window, width/2, height/2);
    }
}

