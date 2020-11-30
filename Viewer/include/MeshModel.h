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
	const std::string& GetModelName() const;
	std::vector<glm::vec3>& get_vertices();

	//void draw_bounding_box(glm::mat4x4& mat);
	void SetLocalOrWorld(int index);
	int GetLocalOrWorld() const;
	const glm::mat4x4& GetTransform() const;
	void SetTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetLTransform() const;
	void SetLTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetWTransform() const;
	void SetWTransform(glm::mat4x4& mat);
	const float Getbuondes(int i) const;
	bool GetBounding_Box() const;
	void SetBounding_Box(bool i);
	const glm::vec3& GetColor() const;
	void SetColor(glm::vec3& mat);

private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::string model_name_;

	int LocalOrWorld;
	bool draw_bounding_box;
	glm::vec3 ModelColor;
	glm::mat4x4 Transform;
	glm::mat4x4 LTransform;
	glm::mat4x4 WTransform;
	float buondes[6];//[max.x,max.y,max.z,min.x,min.y,min.z]
};
