#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Light
{
public:
	Light();
	virtual ~Light();

	void SetTransformation(glm::mat4x4& mat);
	const glm::mat4x4& GetTransformation() const;

	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const;

	void Setambient(const glm::vec3& vec);
	const glm::vec3& Getambient() const;

	void Setdiffuse(const glm::vec3& vec);
	const glm::vec3& Getdiffuse() const;

	void Setspecular(const glm::vec3& vec);
	const glm::vec3& Getspecular() const;

	bool GetPointOrParallel() const;
	void SetPointOrParallel(bool i);

private:

	glm::mat4x4 transformation_;
	glm::vec3 Position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	bool PointOrParallel;
};