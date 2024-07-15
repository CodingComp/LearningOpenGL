#include "Model.h"

bool Model::loadModel(std::string filepath)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return false;
	}

	directory = filepath.substr(0, filepath.find_last_of('/'));

	processNode(scene->mRootNode, scene);
	return true;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Vertices
	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normals
		if(mesh->HasNormals()) {
			// Temp abs for visualizing all sides of an obj
			vector.x = abs(mesh->mNormals[i].x);
			vector.y = abs(mesh->mNormals[i].y);
			vector.z = abs(mesh->mNormals[i].z);
			vertex.Normal = vector;
		} else // Temp coloring to visualize desk
		{
			vector.x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			vector.y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			vector.z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			vertex.Normal = vector;
		}

		vertices.push_back(vertex);
	}

	// Indices
	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		// retrieve all indices of the face and store them in the indices vector
		for(unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(vertices, indices);
}

void Model::move(glm::vec3 pos)
{
	position = pos;
	updateMatrix();
}

void Model::rotate(glm::vec3 rot)
{
	rotation = rot;
	updateMatrix();
}

void Model::updateMatrix()
{
	m_Rotation = glm::rotate(m_Rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_Rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(m_Rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	m_Position = translate(m_Position, position);

	m = m_Position * m_Rotation;
}

void Model::Draw()
{
	for(unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw();
	}
}
