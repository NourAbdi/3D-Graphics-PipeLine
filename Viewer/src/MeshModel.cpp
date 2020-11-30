#include "MeshModel.h"

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	float Max_x = vertices[0].x;
	float Max_y = vertices[0].y;
	float Max_z = vertices[0].z;
	float Min_x = vertices[0].x;
	float Min_y = vertices[0].y;
	float Min_z = vertices[0].z;
	//Inittiating the Transformation matrices
	Transform = LTransform = WTransform = {
	   glm::vec4(1.0f,0.0f,0.0f,0.0f),
	   glm::vec4(0.0f,1.0f,0.0f,0.0f),
	   glm::vec4(0.0f,0.0f,1.0f,0.0f),
	   glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
	bounding_box = LocalOrWorld = 0;
	ModelColor = glm::vec3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < vertices.size(); i++)
	{
		Max_x = (Max_x < vertices[i].x) ? vertices[i].x : Max_x;
		Max_y = (Max_y < vertices[i].y) ? vertices[i].y : Max_y;
		Max_z = (Max_z < vertices[i].z) ? vertices[i].z : Max_z;
		Min_z = (Min_z > vertices[i].z) ? vertices[i].z : Min_z;
		Min_y = (Min_y > vertices[i].y) ? vertices[i].y : Min_y;
		Min_x = (Min_x > vertices[i].x) ? vertices[i].x : Min_x;
	}
	buondes[0] = Max_x;
	buondes[1] = Max_y;
	buondes[2] = Max_z;
	buondes[3] = Min_x;
	buondes[4] = Min_y;
	buondes[5] = Min_z;
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

const glm::mat4x4& MeshModel::GetTransform() const
{
	return Transform;
}
void MeshModel::SetTransform(glm::mat4x4& mat)
{
	Transform = mat;
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

const float MeshModel::Getbuondes(int i) const
{
	return buondes[i];
}

bool MeshModel::Getbounding_box() const
{
	return bounding_box;
}
void MeshModel::Setbounding_box(bool i)
{
	bounding_box = i;
}

bool MeshModel::Getfaces_normals() const
{
	return faces_normals;
}
void MeshModel::Setfaces_normals(bool i)
{
	faces_normals = i;
}

bool MeshModel::Getvertices_normals() const
{
	return vertices_normals;
}
void MeshModel::Setvertices_normals(bool i)
{
	vertices_normals = i;
}

const glm::vec3& MeshModel::GetColor() const
{
	return ModelColor;
}
void MeshModel::SetColor(glm::vec3& vec)
{
	ModelColor = vec;
}