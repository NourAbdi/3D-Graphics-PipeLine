#pragma once

#include <vector>
#include <memory>

#include "Camera.h"
#include "MeshModel.h"
#include "Light.h"

class Scene {
public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	MeshModel& GetModel(int index) const;
	MeshModel& GetActiveModel() const;
	
	void AddCamera(const std::shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index) const;
	Camera& GetActiveCamera() const;

	void AddLight(const std::shared_ptr<Light>& light);
	int GetLightCount() const;
	Light& GetLight(int index) const;
	Light& GetActiveLight() const;

	void SetActiveLightIndex(int index);
	int GetActiveLightIndex() const;

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;

private:
	std::vector<std::shared_ptr<MeshModel>> mesh_models_;
	std::vector<std::shared_ptr<Camera>> cameras_;
	std::vector<std::shared_ptr<Light>> lights_;
	
	int active_camera_index_;
	int active_model_index_;
	int active_light_index_;
};