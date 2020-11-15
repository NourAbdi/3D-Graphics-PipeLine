#include "MeshModel.h"

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	//Inittiating the Transformation matrices
	Translate = Scale = Rotate = {
	   glm::vec4(1.0f,0.0f,0.0f,0.0f),
	   glm::vec4(0.0f,1.0f,0.0f,0.0f),
	   glm::vec4(0.0f,0.0f,1.0f,0.0f),
	   glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
	LocalOrWorld = 0;
}

MeshModel::~MeshModel()
{
}

const Face& MeshModel::GetFace(int index) const
{
	return faces_[index];
}

int MeshModel::GetFacesCount() const
{
	return faces_.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name_;
}

std::vector<glm::vec3>& MeshModel::get_vertices() {
	return vertices_;
}

/******************Setters&Getters*****************/
void MeshModel::SetLocalOrWorld(int index)
{
	LocalOrWorld = index;
}
int MeshModel::GetLocalOrWorld() const
{
	return LocalOrWorld;
}

const glm::mat4x4& MeshModel::DoTransformation() const
{
	glm::mat4x4 Trans = GetTranslate() * GetRotate() * GetScale();
	return Trans;
}

const glm::mat4x4& MeshModel::GetTranslate() const
{
	return Translate;
}
void MeshModel::SetTranslate(glm::mat4x4& mat)
{
	Translate = mat;
}

const glm::mat4x4& MeshModel::GetScale() const
{
	return Scale;
}
void MeshModel::SetScale(glm::mat4x4& mat)
{
	Scale = mat;
}

const glm::mat4x4& MeshModel::GetRotate() const
{
	return Rotate;
}
void MeshModel::SetRotate(glm::mat4x4& mat)
{
	Rotate = mat;
}