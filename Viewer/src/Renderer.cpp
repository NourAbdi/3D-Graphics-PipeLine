#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Renderer.h"
#include "InitShader.h"
#include <iostream>
#include <glm/gtx/transform.hpp>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
#define Radius1 200
#define Radius2 100
#define pi  3.14159 
#define NDegrees 100
#define Teta 2*pi/NDegrees

static int Flag = 0;
static glm::vec3 black(0.0f, 0.0f, 0.0f);
static glm::vec3 white(255.0f, 255.0f, 255.0f);

Renderer::Renderer(int viewport_width, int viewport_height) :
	viewport_width_(viewport_width),
	viewport_height_(viewport_height)
{
	InitOpenGLRendering();
	CreateBuffers(viewport_width, viewport_height);
}
void Renderer::LoadTextures()
{
	if (!texture1.loadTexture("bin\\Debug\\wood.jpg", true))
	{
		texture1.loadTexture("bin\\Release\\wood.jpg", true);
	}
}
Renderer::~Renderer()
{
	delete[] color_buffer_;
	delete[] z_buffer_;
}
void Renderer::LoadShaders()
{
	Shader.loadShaders("vshader.glsl", "fshader.glsl");
}
void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width_) return;
	if (j < 0) return; if (j >= viewport_height_) return;

	color_buffer_[INDEX(viewport_width_, i, j, 0)] = color.x;
	color_buffer_[INDEX(viewport_width_, i, j, 1)] = color.y;
	color_buffer_[INDEX(viewport_width_, i, j, 2)] = color.z;
}
void Renderer::PutPixel(const int i, const int j, const float z, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width_) return;
	if (j < 0) return; if (j >= viewport_height_) return;
	if (z < z_buffer_[i*viewport_height_ + j])
	{
		z_buffer_[i*viewport_height_ + j] = z;
		color_buffer_[INDEX(viewport_width_, i, j, 0)] = color.x;
		color_buffer_[INDEX(viewport_width_, i, j, 1)] = color.y;
		color_buffer_[INDEX(viewport_width_, i, j, 2)] = color.z;
	}
}

void Renderer::plotLineLow(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
{
	int y, D;
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = (2 * dy) - dx;
	y = p1.y;

	for (int i = p1.x; i <= p2.x; i++)
	{
		PutPixel(i, y, color);
		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
			D = D + 2 * dy;
	}
}

void Renderer::plotLineHigh(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
{
	int x, D;
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	x = p1.x;

	for (int i = p1.y; i <= p2.y; i++)
	{
		PutPixel(x, i, color);
		if (D > 0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else
			D = D + 2 * dx;
	}
}

float Renderer::max_point(const float x, const float y, const float z)
{
	return ((x >= y) ? x : y) >= z ? ((x >= y) ? x : y) : z;
}
float Renderer::min_point(const float x, const float y, const float z)
{
	return ((x <= y) ? x : y) <= z ? ((x <= y) ? x : y) : z;
}
float Renderer::cal_area(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
{
	return ((float)((c.x - a.x) * (b.y - a.y)) - (float)((c.y - a.y) * (b.x - a.x)));
}
void Renderer::DrawTriangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
	const glm::vec3& color, bool fog, float fog_start, float fog_end, const glm::vec3& FogColor)
{
	float Maxx = max_point(p1.x, p2.x, p3.x);
	float Maxy = max_point(p1.y, p2.y, p3.y);
	float Minx = min_point(p1.x, p2.x, p3.x);
	float Miny = min_point(p1.y, p2.y, p3.y);
	float AREA = cal_area(p3, p2, p1);
	float A;
	float B;
	float C;
	float Z;
	float f;
	glm::vec3 Color(black);

	for (int j = Miny; j < Maxy; j++)
	{
		for (int i = Minx; i < Maxx; i++)
		{
			A = cal_area(p3, p2, glm::vec2(i, j));
			B = cal_area(p1, p3, glm::vec2(i, j));
			C = cal_area(p2, p1, glm::vec2(i, j));

			if (A >= 0 && B >= 0 && C >= 0)
			{
				Z = (A / AREA)*p1.z + (B / AREA)*p2.z + (C / AREA)*p3.z;
				Color = color;
				if (fog)
				{
					f = (fog_end - Z) / (fog_end - fog_start);
					Color = ((1 - f) * FogColor) + (f * color);
				}
				PutPixel(i, j, Z, Color);
			}
		}
	}
}
void Renderer::DrawTriangle1(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
	const glm::vec3& color1, const glm::vec3& color2, const glm::vec3& color3)
{
	float Maxx = max_point(p1.x, p2.x, p3.x);
	float Maxy = max_point(p1.y, p2.y, p3.y);
	float Minx = min_point(p1.x, p2.x, p3.x);
	float Miny = min_point(p1.y, p2.y, p3.y);
	float AREA = cal_area(p3, p2, p1);
	float A;
	float B;
	float C;
	float Z;
	glm::vec3 color(black);

	for (int j = Miny; j < Maxy; j++)
	{
		for (int i = Minx; i < Maxx; i++)
		{
			A = cal_area(p3, p2, glm::vec2(i, j));
			B = cal_area(p1, p3, glm::vec2(i, j));
			C = cal_area(p2, p1, glm::vec2(i, j));

			if (A >= 0 && B >= 0 && C >= 0)
			{
				Z = (A / AREA)*p1.z + (B / AREA)*p2.z + (C / AREA)*p3.z;
				float colorx = (A / AREA)*color1.x + (B / AREA)*color2.x + (C / AREA)*color3.x;
				float colory = (A / AREA)*color1.y + (B / AREA)*color2.y + (C / AREA)*color3.y;
				float colorz = (A / AREA)*color1.z + (B / AREA)*color2.z + (C / AREA)*color3.z;
				color = glm::vec3(colorx, colory, colorz);
				PutPixel(i, j, Z, color);
			}
		}
	}
}
void Renderer::DrawTriangle2(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
	const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3, const glm::vec3& color,
	bool PointOrParallel, const glm::vec3& ambient, const glm::vec3& diffuse1, const glm::vec3&specular1,
	const glm::vec3& light_position, const glm::vec3& lightDir
)
{
	float Maxx = max_point(p1.x, p2.x, p3.x);
	float Maxy = max_point(p1.y, p2.y, p3.y);
	float Minx = min_point(p1.x, p2.x, p3.x);
	float Miny = min_point(p1.y, p2.y, p3.y);
	float AREA = cal_area(p3, p2, p1);
	float A;
	float B;
	float C;
	float Z;
	float specularStrength = 0.5;
	glm::vec3 diffuse(black);
	glm::vec3 specular(black);
	glm::vec3 n;
	glm::vec3 FragPosition;

	for (int j = Miny; j < Maxy; j++)
	{
		for (int i = Minx; i < Maxx; i++)
		{
			A = cal_area(p3, p2, glm::vec2(i, j));
			B = cal_area(p1, p3, glm::vec2(i, j));
			C = cal_area(p2, p1, glm::vec2(i, j));

			if (A >= 0 && B >= 0 && C >= 0)
			{
				float nx = (A / AREA)*n1.x + (B / AREA)*n2.x + (C / AREA)*n3.x;
				float ny = (A / AREA)*n1.y + (B / AREA)*n2.y + (C / AREA)*n3.y;
				float nz = (A / AREA)*n1.z + (B / AREA)*n2.z + (C / AREA)*n3.z;
				Z = (A / AREA)*p1.z + (B / AREA)*p2.z + (C / AREA)*p3.z;
				FragPosition = glm::normalize(glm::vec3(i, j, Z));
				n = glm::normalize(glm::vec3(nx, ny, nz));

				if (PointOrParallel) // Point light source :
				{
					//// diffuse 
					glm::vec3 norm = glm::normalize(-n);
					glm::vec3 lightDir = glm::normalize(light_position - FragPosition);
					float diff = glm::max(glm::dot(norm, -lightDir), 0.0f);
					diffuse = diff * diffuse1;
					//// specular
					glm::vec3 viewDir = glm::normalize(n);
					glm::vec3 reflectDir = glm::reflect(-lightDir, norm);
					float spec = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32);
					specular = specularStrength * spec * specular1;
				}
				else // Parallel light source :
				{
					//// diffuse 
					glm::vec3 norm = glm::normalize(-n);
					float diff = glm::max(glm::dot(norm, lightDir), 0.0f);
					diffuse = diff * diffuse1;
					//// specula
					glm::vec3 viewDir = glm::normalize(n);
					glm::vec3 reflectDir = glm::reflect(lightDir, norm);
					float spec = glm::pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32);
					specular = specularStrength * spec * specular1;
				}
				glm::vec3 result = (ambient + diffuse + specular) * color;
				result.x = (result.x > 1) ? 1.0f : result.x;
				result.y = (result.y > 1) ? 1.0f : result.y;
				result.z = (result.z > 1) ? 1.0f : result.z;
				PutPixel(i, j, Z, result);
			}
		}
	}
}
void Renderer::DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	if (dy < 0)
		dy = -dy;
	if (dx < 0)
		dx = -dx;

	if (dy < dx)//abs(y1 - y0) < abs(x1 - x0)
		if (p1.x > p2.x)
			plotLineLow(p2, p1, color);
		else
			plotLineLow(p1, p2, color);
	else
		if (p1.y > p2.y)
			plotLineHigh(p2, p1, color);
		else
			plotLineHigh(p1, p2, color);
}
void Renderer::ResizeBuffers(int w, int h)
{
	viewport_height_ = h;
	viewport_width_ = w;
	if (color_buffer_) delete[] color_buffer_;
	delete[] z_buffer_;
	CreateOpenGLBuffer(); //Do not remove this line.
	color_buffer_ = new float[3 * w * h];
	z_buffer_ = new float[w * h];
	ClearColorBuffer(black);
}
void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenGLBuffer(); //Do not remove this line.
	color_buffer_ = new float[3 * w * h];
	z_buffer_ = new float[w * h];
	ClearColorBuffer(black);
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex_);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc_);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc_);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::CreateOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex_);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width_, viewport_height_, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width_, viewport_height_);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex_);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width_, viewport_height_, GL_RGB, GL_FLOAT, color_buffer_);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc_);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width_; i++)
	{
		for (int j = 0; j < viewport_height_; j++)
		{
			z_buffer_[i*viewport_height_ + j] = INFINITY;
			PutPixel(i, j, color);
		}
	}
}

void Renderer::Render(const Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width_ / 2;
	int half_height = viewport_height_ / 2;
	float max1 = 0.0f;
	float max2 = 0.0f;
	float Max = 0.0f;
	float Avg_x = 0.0f;
	float Avg_y = 0.0f;
	float Avg_z = 0.0f;
	float delta = 0.0f;
	float delta_x = 0.0f;
	float delta_y = 0.0f;
	float delta_z = 0.0f;
	glm::mat4 Transformations;
	glm::mat4 ViewTransformations;

	//Drawing Axises :
	DrawLine(glm::vec2(0, half_height), glm::vec2(viewport_width_, half_height), glm::vec3(0.0f, 0.0f, 1.0f));
	DrawLine(glm::vec2(half_width, 0), glm::vec2(half_width, viewport_height_), glm::vec3(1.0f, 0.0f, 0.0f));

	if (scene.GetCameraCount() > 0) //This check if we loaded camera
	{
		Camera &camera = scene.GetActiveCamera(); // Gets active camera 
		glm::mat4x4 Tc = camera.GetViewTransformation();
		glm::mat4x4 Cinv = glm::inverse(Tc);
		glm::vec4 positionhc = (Tc * glm::vec4(camera.GetCameraPosition(), 1.0f));
		glm::vec3 position = (positionhc) / positionhc.w;
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		glm::vec3 at(0.0f, 0.0f, 1.0f);
		glm::mat4x4 ViewMatrix = glm::lookAt(position, at, up);
		glm::mat4x4 projection;

		float fovy = camera.Getfovy();
		float nearP = camera.Getnear();
		float farP = camera.Getfar();
		float Zoom = camera.GetZoom();
		glm::mat4 Zooom
		(
			glm::vec4(Zoom, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, Zoom, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, Zoom, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);

		if (!camera.GetOrthoOrProj())
		{
			projection = camera.GetProjectionTransformation();
		}
		if (camera.GetOrthoOrProj())
		{
			projection = glm::perspective(glm::radians(fovy), static_cast<float>(viewport_width_ / viewport_height_), nearP, farP);
		}

		if (scene.GetModelCount() > 0) //This check if we loaded the mesh model
		{
			MeshModel &model = scene.GetActiveModel(); // Gets active model 

			glm::mat4x4 modelMatrix = model.GetWTransform() * model.GetLTransform();

			Shader.use();
			Shader.setUniform("model", modelMatrix);
			Shader.setUniform("view", ViewMatrix);
			Shader.setUniform("projection", Zooom * projection);

			if (scene.GetLightCount()) {
				Light light = scene.GetActiveLight();
				Shader.setUniform("eyePos", position);
				Shader.setUniform("color", model.GetColor());

				Shader.setUniform("lighting.lightPos", light.GetPosition());
				Shader.setUniform("lighting.ambientColor", light.Getambient());
				Shader.setUniform("lighting.diffuseColor", light.Getdiffuse());
				Shader.setUniform("lighting.specularColor", light.Getspecular());
				Shader.setUniform("lighting.ambientStr", light.Getambientintensity());
				Shader.setUniform("ambientColor", model.Getambient());
				Shader.setUniform("diffuseColor", model.Getdiffuse());
				Shader.setUniform("specularColor", model.Getspecular());
				Shader.setUniform("specularColor", model.Getspecular());

				Shader.setUniform("toonShading", TRUE);

			}

			Shader.setUniform("texture", 0);

			// Set 'texture1' as the active texture at slot #0
			texture1.bind(0);

			//Shader.setUniform("material.textureMap", 0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(model.GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, model.GetModelVertices().size());
			glBindVertexArray(0);
			// Unset 'texture1' as the active texture at slot #0
			texture1.unbind(0);

			// Drag our model's faces (triangles) in line mode (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(model.GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, model.GetModelVertices().size());
			glBindVertexArray(0);

		}
	}
}

void Renderer::SetViewportWidth(int i)
{
	viewport_width_ = i;
}

void Renderer::SetViewportHeight(int i)
{
	viewport_height_ = i;
}

int Renderer::GetViewportWidth() const
{
	return viewport_width_;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height_;
}