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
	
	vbo = new VBO(&mesh->V(0), (sizeof(float)*3) * mesh->NV());
	ebo = new EBO(&mesh->F(0), (mesh->NF()*3) * sizeof(int));

	vao->LinkAttribute(*vbo, 0, 3, GL_FLOAT, sizeof(float) * 3, nullptr);

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
	
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
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
				 glm::rotate(m_Rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
				 glm::rotate(m_Rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	m_Position = translate(m_Position, position);

	m = m_Position * m_Rotation;
}