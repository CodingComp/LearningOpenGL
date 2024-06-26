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
    
    float _left, _right, _bottom, _top, _near, _far, fov;
    float speed = 0.1f;
    float sensitivity = 100.0f;

    GLuint shaderID;
    
    GLint matrixLoc;
    
    glm::mat4 view, projection;

    glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    
public:

    int width, height;
    
    Camera(int width, int height, GLuint shaderID, float left, float right, float bottom, float top, float near, float far, float fov);

    void matrix();
    
    void changePerspective();

    void inputs(GLFWwindow* window);
    
};
