#version 330 core

layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x * 0.05f, aPos.y * 0.05f, aPos.z * 0.05f, 1.0);
}