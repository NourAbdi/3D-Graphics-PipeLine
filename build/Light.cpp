#include "Light.h"
#include <glm/gtx/transform.hpp>


Light::Light()
{
	transformation_ = {
	   glm::vec4(1.0f,0.0f,0.0f,0.0f),
	   glm::vec4(0.0f,1.0f,0.0f,0.0f),
	   glm::vec4(0.0f,0.0f,1.0f,0.0f),
	   glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
	Position = glm::vec3(0.0f, 100.0f, 0.0f);
	ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	specular = glm::vec3(0.0f, 0.0f, 0.0f);
	PointOrParallel = false;
}


Light::~Light()
{
}

void Light::SetTransformation(glm::mat4x4& mat)
{
	transformation_ = mat;
}
const glm::mat4x4& Light::GetTransformation() const
{
	return transformation_;
}

void Light::SetPosition(const glm::vec3& position)
{
	Position = position;
}
const glm::vec3& Light::GetPosition() const
{
	return Position;
}

void Light::Setambient(const glm::vec3& vec)
{
	ambient = vec;
}
const glm::vec3& Light::Getambient() const
{
	return ambient;
}

void Light::Setdiffuse(const glm::vec3& vec)
{
	diffuse = vec;
}
const glm::vec3& Light::Getdiffuse() const
{
	return diffuse;
}

void Light::Setspecular(const glm::vec3& vec)
{
	specular = vec;
}
const glm::vec3& Light::Getspecular() const
{
	return specular;
}

bool Light::GetPointOrParallel() const
{
	return PointOrParallel;
}
void Light::SetPointOrParallel(bool i)
{
	PointOrParallel = i;
}