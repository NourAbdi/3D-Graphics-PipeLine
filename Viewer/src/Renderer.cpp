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

Renderer::~Renderer()
{
	delete[] color_buffer_;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width_) return;
	if (j < 0) return; if (j >= viewport_height_) return;
	
	color_buffer_[INDEX(viewport_width_, i, j, 0)] = color.x;
	color_buffer_[INDEX(viewport_width_, i, j, 1)] = color.y;
	color_buffer_[INDEX(viewport_width_, i, j, 2)] = color.z;
}

void Renderer::plotLineLow(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
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

void Renderer::plotLineHigh(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
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

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
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
			plotLineLow(p2 ,p1 ,color);
		else
			plotLineLow(p1, p2, color);
	else
		if (p1.y > p2.y)
			plotLineHigh(p2, p1, color);
		else
			plotLineHigh(p1, p2, color);
}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenGLBuffer(); //Do not remove this line.
	color_buffer_ = new float[3 * w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
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
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
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
			PutPixel(i, j, color);
		}
	}
}

void Renderer::Render(const Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width_ / 2;
	int half_height = viewport_height_ / 2;
	float max1	= 0.0f;
	float max2	= 0.0f;
	float Max = 0.0f;
	float Avg_x	= 0.0f;
	float Avg_y	= 0.0f;
	float Avg_z	= 0.0f;
	float delta_x = 0.0f;
	float delta_y = 0.0f;
	float delta_z = 0.0f;
	glm::mat4 Transformations;

	//Drawing Axises :
	DrawLine(glm::vec2(0, half_height), glm::vec2(viewport_width_, half_height), glm::vec3(0.0f, 0.0f, 1.0f));
	DrawLine(glm::vec2(half_width, 0), glm::vec2(half_width, viewport_height_), glm::vec3(1.0f, 0.0f, 0.0f));

	if (scene.GetCameraCount() > 0) //This check if we loaded camera
	{
		Camera &camera = scene.GetActiveCamera(); // Gets active camera 
		glm::mat4x4 Tc = camera.GetViewTransformation();
		//glm::mat4x4 Cinv = glm::inverse(Tc);
		glm::vec3 position=camera.GetCameraPosition();
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		glm::vec3 at(0.0f,0.0f,-1.0f);
		glm::mat4x4 ViewMatrix = glm::lookAt(position, at,up);
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
			std::vector<glm::vec3> vertices = model.get_vertices(); // Gets the vertices
			std::vector<glm::vec3> normals = model.get_normals(); // Gets the vertices normals
			glm::mat4 Final_L = model.GetLTransform();
			glm::mat4 Final_W = model.GetWTransform();
			glm::vec3 Model_Color = model.GetColor();

			Avg_x = (model.Getbuondes(0) + model.Getbuondes(3)) / 2;
			Avg_y = (model.Getbuondes(1) + model.Getbuondes(4)) / 2;
			Avg_z = (model.Getbuondes(2) + model.Getbuondes(5)) / 2;
			max1 = (model.Getbuondes(0) - model.Getbuondes(3));
			max2 = (model.Getbuondes(1) - model.Getbuondes(4));
			Max = (max1 < max2) ? max2 : max1;
			delta_x = half_width / Max;
			delta_y = half_height / Max;
			//delta_z = half_height / Max;
			Avg_x = Avg_x * delta_x;
			Avg_y = Avg_y * delta_y;
			Avg_z = Avg_z * delta_z;
			
			glm::mat4 Translate_Back_matt // Translation matrix to put the model in (0,0)
			(
				glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
				glm::vec4(half_width , half_height , 0.0f, 1.0f)
			);
			glm::mat4 Translate_Back_mat // Translation matrix to put the model in (0,0)
			(
				glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
				glm::vec4(-Avg_x, -Avg_y, -Avg_z, 1.0f)
			);
			glm::mat4 Scale_mat // Scaling matrix to adjust the size of the model
			(
				glm::vec4(delta_x, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, delta_y, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, delta_z, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
			);

			//In this case of multiplying matrices ,Order does matter... 
			Transformations =  Translate_Back_matt * Zooom * Scale_mat * projection *  ViewMatrix *Tc * Final_W *  Final_L ;

			for (int faces_c = 0; faces_c < model.GetFacesCount(); faces_c++)
			{
				glm::vec3 p1 = vertices.at(model.GetFace(faces_c).GetVertexIndex(0) - 1);
				glm::vec3 p2 = vertices.at(model.GetFace(faces_c).GetVertexIndex(1) - 1);
				glm::vec3 p3 = vertices.at(model.GetFace(faces_c).GetVertexIndex(2) - 1);
				glm::vec3 n1 = (normals.at(model.GetFace(faces_c).GetNormalIndex(0) - 1) + p1);
				glm::vec3 n2 = (normals.at(model.GetFace(faces_c).GetNormalIndex(1)-1)+p2);
				glm::vec3 n3 = (normals.at(model.GetFace(faces_c).GetNormalIndex(2)-1)+p3);
				glm::vec3 s1 (((p1.x+p2.x+p3.x)/3), ((p1.y + p2.y + p3.y) / 3), ((p1.z + p2.z + p3.z) / 3));
				glm::vec3 s2 (glm::normalize(glm::cross(p2-p1, p3-p1))+s1);
				
				//from 1x3 to 1x4
				glm::vec4 v1(p1, 1.0f);
				glm::vec4 v2(p2, 1.0f);
				glm::vec4 v3(p3, 1.0f);
				glm::vec4 v4(s1, 1.0f);
				glm::vec4 v5(s2, 1.0f);
				glm::vec4 u1(n1, 1.0f);
				glm::vec4 u2(n2, 1.0f);
				glm::vec4 u3(n3, 1.0f);
				
				v1 = Transformations * v1;
				v2 = Transformations * v2;
				v3 = Transformations * v3;
				v4 = Transformations * v4;
				v5 = Transformations * v5;
				u1 = Transformations * u1;
				u2 = Transformations * u2;
				u3 = Transformations * u3;
		
				//To draw the mish model lines we need to convert the cordinates from 1x4 to 1x2 :
				//Lines color is default black...
				glm::vec2 d1(v1.x/v1.w, v1.y/v1.w);
				glm::vec2 d2(v2.x/v2.w, v2.y/v2.w);
				glm::vec2 d3(v3.x/v3.w, v3.y/v3.w);
				glm::vec2 d4(v4.x/v4.w, v4.y/v4.w);
				glm::vec2 d5(v5.x/v5.w, v5.y/v5.w);
				glm::vec2 d6(u1.x/u1.w, u1.y/u1.w);
				glm::vec2 d7(u2.x/u2.w, u2.y/u2.w);
				glm::vec2 d8(u3.x/u3.w, u3.y/u3.w);
			
				DrawLine(d1,d2, Model_Color);
				DrawLine(d1,d3, Model_Color);
				DrawLine(d2,d3, Model_Color);
				if (model.Getfaces_normals())
				{
					DrawLine(d4, d5, black);
				}
				if (model.Getvertices_normals())
				{
					DrawLine(d6, d1, black);
					DrawLine(d7, d2, black);
					DrawLine(d8, d3, black);
				}
			}
			glm::vec4 u1(model.Getbuondes(0), model.Getbuondes(1), model.Getbuondes(2), 1.0f);
			glm::vec4 u2(model.Getbuondes(0), model.Getbuondes(1), model.Getbuondes(5), 1.0f);
			glm::vec4 u3(model.Getbuondes(0), model.Getbuondes(4), model.Getbuondes(2), 1.0f);
			glm::vec4 u4(model.Getbuondes(0), model.Getbuondes(4), model.Getbuondes(5), 1.0f);
			glm::vec4 u5(model.Getbuondes(3), model.Getbuondes(1), model.Getbuondes(2), 1.0f);
			glm::vec4 u6(model.Getbuondes(3), model.Getbuondes(1), model.Getbuondes(5), 1.0f);
			glm::vec4 u7(model.Getbuondes(3), model.Getbuondes(4), model.Getbuondes(2), 1.0f);
			glm::vec4 u8(model.Getbuondes(3), model.Getbuondes(4), model.Getbuondes(5), 1.0f);
		
			u1 = Transformations * u1;
			u2 = Transformations * u2;
			u3 = Transformations * u3;
			u4 = Transformations * u4;
			u5 = Transformations * u5;
			u6 = Transformations * u6;
			u7 = Transformations * u7;
			u8 = Transformations * u8;
			
		
			//To draw the mish model lines we need to convert the cordinates from 1x4 to 1x2 :
			//Lines color is default black...
			glm::vec2 s1(u1.x/u1.w , u1.y/u1.w);
			glm::vec2 s2(u2.x/u2.w , u2.y/u2.w);
			glm::vec2 s3(u3.x/u3.w , u3.y/u3.w);
			glm::vec2 s4(u4.x/u4.w , u4.y/u4.w);
			glm::vec2 s5(u5.x/u5.w , u5.y/u5.w);
			glm::vec2 s6(u6.x/u6.w , u6.y/u6.w);
			glm::vec2 s7(u7.x/u7.w , u7.y/u7.w);
			glm::vec2 s8(u8.x/u8.w , u8.y/u8.w);
			if (model.Getbounding_box())
			{
				DrawLine(s1, s2, black);
				DrawLine(s1, s3, black);
				DrawLine(s1, s5, black);
				DrawLine(s2, s4, black);
				DrawLine(s2, s6, black);
				DrawLine(s3, s4, black);
				DrawLine(s3, s7, black);
				DrawLine(s4, s8, black);
				DrawLine(s5, s6, black);
				DrawLine(s5, s7, black);
				DrawLine(s6, s8, black);
				DrawLine(s7, s8, black);
			}
		}
	}
	//Active model is the last opened file ( last read obj file)
	//if ((scene.GetModelCount() > 0) && (!scene.Getuse_camera())) //This check if we loaded the mesh model
	//{
	//	MeshModel &model = scene.GetActiveModel(); // Gets active model 
	//	std::vector<glm::vec3> vertices = model.get_vertices(); // Gets the vertices
	//	std::vector<glm::vec3> normals = model.get_normals(); // Gets the vertices normals
	//	glm::mat4 Final_L = model.GetLTransform();
	//	glm::mat4 Final_W = model.GetWTransform();
	//	glm::vec3 Model_Color = model.GetColor();
	//
	//	Avg_x = (model.Getbuondes(0) + model.Getbuondes(3)) / 2;
	//	Avg_y = (model.Getbuondes(1) + model.Getbuondes(4)) / 2;
	//	Avg_z = (model.Getbuondes(2) + model.Getbuondes(5)) / 2;
	//	max1 = (model.Getbuondes(0) - model.Getbuondes(3));
	//	max2 = (model.Getbuondes(1) - model.Getbuondes(4));
	//	delta_x = half_width / max1;
	//	delta_y = half_height / max2;
	//	delta_z = half_height / max2;
	//	Avg_x = Avg_x * delta_x;
	//	Avg_y = Avg_y * delta_y;
	//	Avg_z = Avg_z * delta_z;
	//
	//	glm::mat4 Translate_Back_matt // Translation matrix to put the model in (0,0)
	//	(
	//		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
	//		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
	//		glm::vec4( half_width, half_height, 0.0f, 1.0f)
	//	); 
	//	glm::mat4 Translate_Back_mat // Translation matrix to put the model in (0,0)
	//	(
	//		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
	//		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
	//		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
	//		glm::vec4(-Avg_x, -Avg_y, -Avg_z, 1.0f)
	//	);
	//	glm::mat4 Scale_mat // Scaling matrix to adjust the size of the model
	//	(
	//		glm::vec4(delta_x, 0.0f, 0.0f, 0.0f),
	//		glm::vec4(0.0f, delta_y, 0.0f, 0.0f),
	//		glm::vec4(0.0f, 0.0f, delta_z, 0.0f),
	//		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	//	);
	//	
	//	//In this case of multiplying matrices ,Order does matter... 
	//	Transformations = Final_W * Translate_Back_matt * Final_L * Translate_Back_mat * Scale_mat;
	//	//model.SetTransform(Transformations);
	//
	//	for (int faces_c = 0; faces_c < model.GetFacesCount(); faces_c++)
	//	{
	//		glm::vec3 p1 = vertices.at(model.GetFace(faces_c).GetVertexIndex(0)-1);
	//		glm::vec3 p2 = vertices.at(model.GetFace(faces_c).GetVertexIndex(1)-1);
	//		glm::vec3 p3 = vertices.at(model.GetFace(faces_c).GetVertexIndex(2)-1);
	//		glm::vec3 n1 = (normals.at(model.GetFace(faces_c).GetNormalIndex(0)-1)+p1);
	//		glm::vec3 n2 = (normals.at(model.GetFace(faces_c).GetNormalIndex(1)-1)+p2);
	//		glm::vec3 n3 = (normals.at(model.GetFace(faces_c).GetNormalIndex(2)-1)+p3);
	//		glm::vec3 s1 (((p1.x+p2.x+p3.x)/3), ((p1.y + p2.y + p3.y) / 3), ((p1.z + p2.z + p3.z) / 3));
	//		glm::vec3 s2 (glm::normalize(glm::cross(p2-p1, p3-p1))+s1);
	//		
	//		//from 1x3 to 1x4
	//		glm::vec4 v1(p1, 1.0f);
	//		glm::vec4 v2(p2, 1.0f);
	//		glm::vec4 v3(p3, 1.0f);
	//		glm::vec4 v4(s1, 1.0f);
	//		glm::vec4 v5(s2, 1.0f);
	//		glm::vec4 u1(n1, 1.0f);
	//		glm::vec4 u2(n2, 1.0f);
	//		glm::vec4 u3(n3, 1.0f);
	//		
	//		v1 = Transformations * v1;
	//		v2 = Transformations * v2;
	//		v3 = Transformations * v3;
	//		v4 = Transformations * v4;
	//		v5 = Transformations * v5;
	//		u1 = Transformations * u1;
	//		u2 = Transformations * u2;
	//		u3 = Transformations * u3;
	//
	//		//To draw the mish model lines we need to convert the cordinates from 1x4 to 1x2 :
	//		//Lines color is default black...
	//		glm::vec2 d1(v1.x, v1.y);
	//		glm::vec2 d2(v2.x, v2.y);
	//		glm::vec2 d3(v3.x, v3.y);
	//		glm::vec2 d4(v4.x, v4.y);
	//		glm::vec2 d5(v5.x, v5.y);
	//		glm::vec2 d6(u1.x, u1.y);
	//		glm::vec2 d7(u2.x, u2.y);
	//		glm::vec2 d8(u3.x, u3.y);
	//	
	//		DrawLine(d1,d2, Model_Color);
	//		DrawLine(d1,d3, Model_Color);
	//		DrawLine(d2,d3, Model_Color);
	//		if (model.Getfaces_normals())
	//		{
	//			DrawLine(d4, d5, black);
	//		}
	//		if (model.Getvertices_normals())
	//		{
	//			DrawLine(d6, d1, black);
	//			DrawLine(d7, d2, black);
	//			DrawLine(d8, d3, black);
	//		}
	//	}
	//	glm::vec4 u1(model.Getbuondes(0), model.Getbuondes(1), model.Getbuondes(2), 1.0f);
	//	glm::vec4 u2(model.Getbuondes(0), model.Getbuondes(1), model.Getbuondes(5), 1.0f);
	//	glm::vec4 u3(model.Getbuondes(0), model.Getbuondes(4), model.Getbuondes(2), 1.0f);
	//	glm::vec4 u4(model.Getbuondes(0), model.Getbuondes(4), model.Getbuondes(5), 1.0f);
	//	glm::vec4 u5(model.Getbuondes(3), model.Getbuondes(1), model.Getbuondes(2), 1.0f);
	//	glm::vec4 u6(model.Getbuondes(3), model.Getbuondes(1), model.Getbuondes(5), 1.0f);
	//	glm::vec4 u7(model.Getbuondes(3), model.Getbuondes(4), model.Getbuondes(2), 1.0f);
	//	glm::vec4 u8(model.Getbuondes(3), model.Getbuondes(4), model.Getbuondes(5), 1.0f);
	//
	//	u1 = Transformations * u1;
	//	u2 = Transformations * u2;
	//	u3 = Transformations * u3;
	//	u4 = Transformations * u4;
	//	u5 = Transformations * u5;
	//	u6 = Transformations * u6;
	//	u7 = Transformations * u7;
	//	u8 = Transformations * u8;
	//	
	//
	//	//To draw the mish model lines we need to convert the cordinates from 1x4 to 1x2 :
	//	//Lines color is default black...
	//	glm::vec2 s1(u1.x , u1.y);
	//	glm::vec2 s2(u2.x , u2.y);
	//	glm::vec2 s3(u3.x , u3.y);
	//	glm::vec2 s4(u4.x , u4.y);
	//	glm::vec2 s5(u5.x , u5.y);
	//	glm::vec2 s6(u6.x , u6.y);
	//	glm::vec2 s7(u7.x , u7.y);
	//	glm::vec2 s8(u8.x , u8.y);
	//	if (model.Getbounding_box())
	//	{
	//		DrawLine(s1, s2, black);
	//		DrawLine(s1, s3, black);
	//		DrawLine(s1, s5, black);
	//		DrawLine(s2, s4, black);
	//		DrawLine(s2, s6, black);
	//		DrawLine(s3, s4, black);
	//		DrawLine(s3, s7, black);
	//		DrawLine(s4, s8, black);
	//		DrawLine(s5, s6, black);
	//		DrawLine(s5, s7, black);
	//		DrawLine(s6, s8, black);
	//		DrawLine(s7, s8, black);
	//	}
	//}
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