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

	void SetLocalOrWorld(int index);
	int GetLocalOrWorld() const;
	const glm::mat4x4& DoTransformation() const;
	const glm::mat4x4& GetTranslate() const;
	void SetTranslate(glm::mat4x4& mat);
	const glm::mat4x4& GetScale() const;
	void SetScale(glm::mat4x4& mat);
	const glm::mat4x4& GetRotate() const;
	void SetRotate(glm::mat4x4& mat);

private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::string model_name_;

	int LocalOrWorld;
	glm::mat4x4 Translate;
	glm::mat4x4 Scale;
	glm::mat4x4 Rotate;
};
