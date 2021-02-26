#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void LoadShaders();
	void Render(const Scene& scene);
	void SwapBuffers();
	void LoadTextures();

	void ClearColorBuffer(const glm::vec3& color);
	void SetViewportWidth(int i);
	void SetViewportHeight(int i);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	void ResizeBuffers(int w, int h);
private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void PutPixel(const int i, const int j,const float z, const glm::vec3& color);
	float max_point(const float x, const float y, const float z);
	float min_point(const float x, const float y, const float z);
	float cal_area(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3);
	void DrawTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
						const glm::vec3& color, bool fog, float fog_start, float fog_end, const glm::vec3& FogColor);
	void DrawTriangle1(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
						const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3);
	void DrawTriangle2(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
						const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3, const glm::vec3& color,
						bool PointOrParallel, const glm::vec3& ambient, const glm::vec3& diffuse1, const glm::vec3&specular1,
						const glm::vec3& light_position, const glm::vec3& lightDir
	);
	void DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color);
	void plotLineLow(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color);
	void plotLineHigh(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color);
	
	
	void CreateBuffers(int w, int h);
	void CreateOpenGLBuffer();
	void InitOpenGLRendering();
	ShaderProgram Shader;
	Texture2D texture1;

	float* color_buffer_;
	float* z_buffer_;
	int viewport_width_;
	int viewport_height_;
	GLuint gl_screen_tex_;
	GLuint gl_screen_vtc_;
};
