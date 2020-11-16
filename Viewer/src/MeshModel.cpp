#include "MeshModel.h"

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	//Inittiating the Transformation matrices
	LTransform = WTransform = LTranslate = LScale = LRotate = WTranslate = WScale = WRotate = {
	   glm::vec4(1.0f,0.0f,0.0f,0.0f),
	   glm::vec4(0.0f,1.0f,0.0f,0.0f),
	   glm::vec4(0.0f,0.0f,1.0f,0.0f),
	   glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
	LocalOrWorld = 0;
	ModelColor = glm::vec3(0.0f, 0.0f, 0.0f);
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

const glm::mat4x4& MeshModel::DoLTransformation() const
{
	glm::mat4x4 Trans = GetLTranslate() * GetLRotate() * GetLScale();
	return Trans;
}

const glm::mat4x4& MeshModel::DoWTransformation() const
{
	glm::mat4x4 Trans = GetWTranslate() * GetWRotate() * GetWScale();
	return Trans;
}

const glm::mat4x4& MeshModel::GetLTransform() const
{
	return LTransform;
}
void MeshModel::SetLTransform(glm::mat4x4& mat)
{
	LTransform = mat;
}

const glm::mat4x4& MeshModel::GetWTransform() const
{
	return WTransform;
}
void MeshModel::SetWTransform(glm::mat4x4& mat)
{
	WTransform = mat;
}

const glm::mat4x4& MeshModel::GetLTranslate() const
{
	return LTranslate;
}
void MeshModel::SetLTranslate(glm::mat4x4& mat)
{
	LTranslate = mat;
}

const glm::mat4x4& MeshModel::GetWTranslate() const
{
	return WTranslate;
}
void MeshModel::SetWTranslate(glm::mat4x4& mat)
{
	WTranslate = mat;
}

const glm::mat4x4& MeshModel::GetLScale() const
{
	return LScale;
}
void MeshModel::SetLScale(glm::mat4x4& mat)
{
	LScale = mat;
}

const glm::mat4x4& MeshModel::GetWScale() const
{
	return WScale;
}
void MeshModel::SetWScale(glm::mat4x4& mat)
{
	WScale = mat;
}

const glm::mat4x4& MeshModel::GetLRotate() const
{
	return LRotate;
}
void MeshModel::SetLRotate(glm::mat4x4& mat)
{
	LRotate = mat;
}

const glm::mat4x4& MeshModel::GetWRotate() const
{
	return WRotate;
}
void MeshModel::SetWRotate(glm::mat4x4& mat)
{
	WRotate = mat;
}

const glm::vec3& MeshModel::GetColor() const
{
	return ModelColor;
}
void MeshModel::SetColor(glm::vec3& vec)
{
	ModelColor = vec;
}