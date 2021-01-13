#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

class MeshModel
{
public:
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	int GetNormalsCount() const;
	const std::string& GetModelName() const;
	std::vector<glm::vec3>& get_vertices();
	std::vector<glm::vec3>& get_normals();

	void SetLocalOrWorld(int index);
	int GetLocalOrWorld() const;
	const glm::mat4x4& GetTransform() const;
	void SetTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetLTransform() const;
	void SetLTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetWTransform() const;
	void SetWTransform(glm::mat4x4& mat);
	const float Getbuondes(int i) const;
	bool Getbounding_box() const;
	void Setbounding_box(bool i);
	bool Getfaces_normals() const;
	void Setfaces_normals(bool i);
	bool Getvertices_normals() const;
	void Setvertices_normals(bool i);
	const glm::vec3& GetColor() const;
	void SetColor(glm::vec3& mat);

	void Setambient(const glm::vec3& vec);
	const glm::vec3& Getambient() const;
	void Setdiffuse(const glm::vec3& vec);
	const glm::vec3& Getdiffuse() const;
	void Setspecular(const glm::vec3& vec);
	const glm::vec3& Getspecular() const;

private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::string model_name_;

	int LocalOrWorld;
	bool bounding_box;
	bool faces_normals;
	bool vertices_normals;
	glm::vec3 ModelColor;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::mat4x4 Transform;
	glm::mat4x4 LTransform;
	glm::mat4x4 WTransform;
	float buondes[6];			//[max.x,max.y,max.z,min.x,min.y,min.z]
};
