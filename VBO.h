#pragma once

#include <glad/glad.h>

#include "Vertex.h"

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
	VBO(Vertex* data, GLsizeiptr size);
	
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
