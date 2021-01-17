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

	void SetDirection(const glm::vec3& direction);
	const glm::vec3& GetDirection() const;

	void Setambient(const glm::vec3& vec);
	const glm::vec3& Getambient() const;

	void Setambientintensity(const float intensity);
	const float Getambientintensity() const;

	void Setdiffuse(const glm::vec3& vec);
	const glm::vec3& Getdiffuse() const;

	void Setspecular(const glm::vec3& vec);
	const glm::vec3& Getspecular() const;

	int Getshading_kind() const;
	void Setshading_kind(int i);

	bool GetPointOrParallel() const;
	void SetPointOrParallel(bool i);

	bool GetFog() const;
	void SetFog(bool i);

	float GetfogStart() const;
	void SetfogStart(float i);

	float GetfogEnd() const;
	void SetfogEnd(float i);

	void SetFogColor(const glm::vec3& vec);
	const glm::vec3& GetFogColor() const;

private:

	glm::mat4x4 transformation_;
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 ambient;
	float ambientintensity;
	float fogStart;
	float fogEnd;
	int shading_kind;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 FogColor;
	bool PointOrParallel;
	bool Fog;
};