#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	active_camera_index_(0),
	active_model_index_(0)
{
	//Inittiating the Transformation matrices
	 Translate = Scale = Rotate ={
		glm::vec4(1.0f,0.0f,0.0f,0.0f),
		glm::vec4(0.0f,1.0f,0.0f,0.0f),
		glm::vec4(0.0f,0.0f,1.0f,0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
	};
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& mesh_model)
{
	mesh_models_.push_back(mesh_model);
}

int Scene::GetModelCount() const
{
	return mesh_models_.size();
}

MeshModel& Scene::GetModel(int index) const
{
	return *mesh_models_[index];
}

MeshModel& Scene::GetActiveModel() const
{
	return *mesh_models_[active_model_index_];
}

void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{
	cameras_.push_back(camera);
}

int Scene::GetCameraCount() const
{
	return cameras_.size();
}

Camera& Scene::GetCamera(int index)
{
	return *cameras_[index];
}

Camera& Scene::GetActiveCamera()
{
	return *cameras_[active_camera_index_];
}

void Scene::SetActiveCameraIndex(int index)
{
	active_camera_index_ = index;
}

int Scene::GetActiveCameraIndex() const
{
	return active_camera_index_;
}

void Scene::SetActiveModelIndex(int index)
{
	active_model_index_ = index;
}

int Scene::GetActiveModelIndex() const
{
	return active_model_index_;
}

void Scene::SetLocalOrWorld(int index)
{
	LocalOrWorld = index;
}
int Scene::GetLocalOrWorld() const
{
	return LocalOrWorld;
}

/******************Setters&Getters*****************/
const glm::mat4x4& Scene::GetTranslate() const
{
	return Translate;
}
void Scene::SetTranslate(glm::mat4x4& mat)
{
	Translate = mat;
}

const glm::mat4x4& Scene::GetScale() const
{
	return Scale;
}
void Scene::SetScale(glm::mat4x4& mat)
{
	Scale = mat;
}

const glm::mat4x4& Scene::GetRotate() const
{
	return Rotate;
}
void Scene::SetRotate(glm::mat4x4& mat)
{
	Rotate = mat;
}