#pragma once

#include <cy/cyVector.h>
#include <glad/glad.h>

class VBO
{
public:
	// ID reference for the Vertex Buffer Object
	GLuint ID;

	/**
	 *  Creates a buffer for new object in the scene.
	 * 
	 * @param data Buffer data containing information such as, vertex position, color, etc.
	 * @param size Total size (in bytes) of buffer.
	 */
	VBO(cy::Vec3<GLfloat>* data, GLsizeiptr size);

	/**
	 * Binds Buffer
	 */
	void Bind();

	/**
	 * Unbinds Buffer
	 */
	void Unbind();

	/**
	 * Deletes Buffer
	 */
	void Delete();
};
