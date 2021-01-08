#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewportWidth(int i);
	void SetViewportHeight(int i);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	
private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void TopTriangle(const glm::ivec2& medp, const glm::ivec2& med2p, const glm::ivec2& minp, const glm::vec3& color);
	void BotTriangle(const glm::ivec2& maxp, const glm::ivec2& medp, const glm::ivec2& med2p, const glm::vec3& color);
	void DrawTriangle(const glm::ivec2& p1, const glm::ivec2& p2, const glm::ivec2& p3, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);
	void plotLineLow(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);
	void plotLineHigh(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);

	void CreateBuffers(int w, int h);
	void CreateOpenGLBuffer();
	void InitOpenGLRendering();

	float* color_buffer_;
	int viewport_width_;
	int viewport_height_;
	GLuint gl_screen_tex_;
	GLuint gl_screen_vtc_;
};
