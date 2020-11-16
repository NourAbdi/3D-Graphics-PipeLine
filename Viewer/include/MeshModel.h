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
	const glm::mat4x4& DoLTransformation() const;
	const glm::mat4x4& DoWTransformation() const;
	const glm::mat4x4& GetLTransform() const;
	void SetLTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetWTransform() const;
	void SetWTransform(glm::mat4x4& mat);
	const glm::mat4x4& GetLTranslate() const;
	void SetLTranslate(glm::mat4x4& mat);
	const glm::mat4x4& GetWTranslate() const;
	void SetWTranslate(glm::mat4x4& mat);
	const glm::mat4x4& GetLScale() const;
	void SetLScale(glm::mat4x4& mat);
	const glm::mat4x4& GetWScale() const;
	void SetWScale(glm::mat4x4& mat);
	const glm::mat4x4& GetLRotate() const;
	void SetLRotate(glm::mat4x4& mat);
	const glm::mat4x4& GetWRotate() const;
	void SetWRotate(glm::mat4x4& mat);
	const glm::vec3& GetColor() const;
	void SetColor(glm::vec3& mat);

private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::string model_name_;

	int LocalOrWorld;
	glm::vec3 ModelColor;
	glm::mat4x4 LTransform;
	glm::mat4x4 WTransform;
	glm::mat4x4 LTranslate;
	glm::mat4x4 LScale;
	glm::mat4x4 LRotate;
	glm::mat4x4 WTranslate;
	glm::mat4x4 WScale;
	glm::mat4x4 WRotate;
};
