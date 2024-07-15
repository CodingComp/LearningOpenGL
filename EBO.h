#pragma once

#include <glad/glad.h>

class EBO
{
public:
	// ID reference for the Elements Buffer Object
	GLuint ID;

	/**
	 *  Creates a element buffer for new object in the scene.
	 * 
	 * @param indices Element buffer indices data.
	 * @param size Total size (in bytes) of element buffer.
	 */
	EBO(unsigned int* indices, GLsizeiptr size);
	
	/**
	 * Binds Elements Buffer
	 */
	void Bind();

	/**
	 * Binds Elements Buffer
	 */
	void Unbind();

	/**
	 * Binds Elements Buffer
	 */
	void Delete();
};
