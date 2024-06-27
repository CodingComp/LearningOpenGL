#pragma once

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
    // ID reference for the Vertex Array Object
    GLuint ID;

    /**
     * Generates vertex array.
     */
    VAO();

    /**
     * 
     * @param VBO Virtual buffer array to set attributes to.
     * @param layout Index of vertex attribute pointer.
     * @param numComponents Number of components per generic vertex attribute. (Must be 1, 2, 3, 4)
     * @param type Data type of each component.
     * @param stride Specifies the byte offset between consecutive generic vertex attributes.
     * @param offset Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
     */
    void LinkAttribute(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

    /**
     * Binds Vertex Array
     */
    void Bind();

    /**
     * Unbinds Vertex Array 
     */
    void Unbind();

    /**
     * Deletes Vertex Array
     */
    void Delete();
};
