#include "Camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera()
{
	view_transformation_ = projection_transformation_ = lookat = {
	   glm::vec4(1.0f,0.0f,0.0f,0.0f),
	   glm::vec4(0.0f,1.0f,0.0f,0.0f),
	   glm::vec4(0.0f,0.0f,1.0f,0.0f),
	   glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
	Proj_or_Ortho = false ;
	POSITION = glm::vec3 (0.0f,0.0f,10.0f);
}

Camera::~Camera()
{
	
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	lookat = glm::lookAt(eye, at, up);
}

void Camera::SetProjectionTransformation(glm::mat4x4& mat)
{
	projection_transformation_ = mat;
}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation_;
}

void Camera::SetViewTransformation(glm::mat4x4& mat)
{
	view_transformation_ = mat;
}

const glm::mat4x4& Camera::GetViewTransformation() const
{
	return view_transformation_;
}

void Camera::Setfovy(const float i)
{
	fovy = i;
}
void Camera::Setnear(const float i)
{
	nearP = i;
}
void Camera::Setfar(const float i)
{
	farP = i;
}
void Camera::SetZoom(const float i)
{
	Zoom = i;
}
const float Camera::Getfovy() const
{
	return fovy;
}
const float Camera::Getnear() const
{
	return nearP;
}
const float Camera::Getfar() const
{
	return farP;
}
const float Camera::GetZoom() const
{
	return Zoom;
}

void Camera::SetCameraPosition(const glm::vec3& position)
{
	POSITION = position;
}

const glm::vec3& Camera::GetCameraPosition() const
{
	return POSITION;
}

bool Camera::GetOrthoOrProj() const
{
	return Proj_or_Ortho;
}
void Camera::SetOrthoOrProj(bool i)
{
	Proj_or_Ortho = i;
}

//void Camera::Ortho(float l, float r, float b, float t, float n, float f)
//{
//	projection_transformation_ =
//	{
//					glm::vec4(	2 / (r - l)		, 0.0f ,	 0.0f ,		0.0f	),
//					glm::vec4(	0.0f ,		 2 / (t - b) ,	 0.0f ,		0.0f	),
//					glm::vec4(	0.0f ,		0.0f ,		 2 / (n - f) ,	0.0f	),
//					glm::vec4((r + l) / (l - r)	,(b + t) / (b - t)	,(n + f) / (n - f)	,1.0f	)
//	};
//}
//void Camera::Perpective(float l, float r, float b, float t, float n, float f)//float fovy, float aspect, float n, float f???
//{
//
//	projection_transformation_ =
//	{
//					glm::vec4(2*n / (r - l)		, 0.0f ,	 0.0f ,		0.0f),
//					glm::vec4(0.0f ,		 2*n / (t - b) ,	 0.0f ,		0.0f),
//					glm::vec4((r + l) / (r-l)	,(b + t) / (t - b)	,(n + f) / (n - f)	,-1.0f),
//					glm::vec4(0.0f ,		0.0f ,		 2*f*n / (n - f) ,	0.0f)
//	};
//
//}