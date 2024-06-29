#include "ModelObject.h"

ModelObject::ModelObject(const char* filepath)
{
	this->filepath = filepath;
}

bool ModelObject::initialize()
{
	mesh = new cy::TriMesh;
	if(!mesh->LoadFromFileObj(filepath)) {
		return false;
	}

	updateMatrix();

	vao = new VAO();
	vao->Bind();

	vbo = new VBO(&mesh->V(0), sizeof(cy::Vec3f) * mesh->NV());
	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(cy::Vec3f), nullptr);

	vao->Unbind();
	vbo->Unbind();

	return true;
}


void ModelObject::move(glm::vec3 pos)
{
	position = pos;
	updateMatrix();
}

void ModelObject::rotate(glm::vec3 rot)
{
	rotation = rot;
	updateMatrix();
}

void ModelObject::updateMatrix()
{
	// Rotation X Y Z
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_Rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(m_Rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Translate teapot
	m_Position = translate(m_Position, position);

	m = m_Position * m_Rotation;
}
