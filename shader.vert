#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 objectMatrix;
uniform mat4 cameraMatrix;

void main()
{
    gl_Position = cameraMatrix * objectMatrix * vec4(aPos, 1.0);
}