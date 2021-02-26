#include "MeshModel.h"

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords, const std::string& model_name) :
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


	modelVertices.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;
			int normalIndex = currentFace.GetNormalIndex(j) - 1;

			Vertex vertex;
			vertex.position = vertices[vertexIndex];
			vertex.normal = normals[normalIndex];

			if (textureCoords.size() > 0)
			{
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.textureCoords = textureCoords[textureCoordsIndex];
			}

			modelVertices.push_back(vertex);
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);

}

MeshModel::~MeshModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

const Face& MeshModel::GetFace(int index) const
{
	return faces_[index];
}

int MeshModel::GetFacesCount() const
{
	return faces_.size();
}

int MeshModel::GetNormalsCount() const
{
	return normals_.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name_;
}

std::vector<glm::vec3>& MeshModel::get_vertices() {
	return vertices_;
}

std::vector<glm::vec3>& MeshModel::get_normals() {
	return normals_;
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

void MeshModel::Setambient(const glm::vec3& vec)
{
	ambient = vec;
}
const glm::vec3& MeshModel::Getambient() const
{
	return ambient;
}

void MeshModel::Setdiffuse(const glm::vec3& vec)
{
	diffuse = vec;
}
const glm::vec3& MeshModel::Getdiffuse() const
{
	return diffuse;
}

void MeshModel::Setspecular(const glm::vec3& vec)
{
	specular = vec;
}
const glm::vec3& MeshModel::Getspecular() const
{
	return specular;
}

GLuint MeshModel::GetVAO() const
{
	return vao;
}

const std::vector<Vertex>& MeshModel::GetModelVertices()
{
	return modelVertices;
}