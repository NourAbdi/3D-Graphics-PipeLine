#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

	void SetProjectionTransformation(glm::mat4x4& mat);
	const glm::mat4x4& GetProjectionTransformation() const;
	void SetViewTransformation( glm::mat4x4& mat) ;
	const glm::mat4x4& GetViewTransformation() const;
	void Setfovy(const float i);
	void Setnear(const float i);
	void Setfar(const float i);
	void SetZoom(const float i);
	const float Getfovy() const;
	const float Getnear() const;
	const float Getfar() const;
	const float GetZoom() const;
	void SetCameraPosition(const glm::vec3& position);
	const glm::vec3& GetCameraPosition() const;
	bool GetOrthoOrProj() const;
	void SetOrthoOrProj(bool i);
	
private:

	glm::vec3 POSITION;
	float fovy;
	float nearP;
	float farP;
	float Zoom;
	glm::mat4x4 view_transformation_;
	glm::mat4x4 projection_transformation_;
	glm::mat4x4 lookat;
	bool Proj_or_Ortho;
};
