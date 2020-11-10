#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Utils.h"
#include "Renderer.h"
#include "InitShader.h"

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
#define Radius1 200
#define Radius2 100
#define pi  3.14159 
#define NDegrees 100
#define Teta 2*pi/NDegrees

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
	glm::mat4 translate_center // Translation_center matrix  
	(
		glm::vec4(50.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 50.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 50.0f, 0.0f),
		glm::vec4(half_width, half_height, 0.0f, 1.0f)
	);
	//active model is the last opened file ( last read obj file)
	if (scene.GetModelCount() > 0) //this check if we loaded the mesh model
	{
		MeshModel model = scene.GetActiveModel(); // gets active model 
		std::vector<glm::vec3> vertices = model.get_vertices(); // gets the vertices
		
		for (int faces_c = 0; faces_c < model.GetFacesCount(); faces_c++)
		{
			glm::vec3 p1 = vertices.at(model.GetFace(faces_c).GetVertexIndex(0)-1);
			glm::vec3 p2 = vertices.at(model.GetFace(faces_c).GetVertexIndex(1)-1);
			glm::vec3 p3 = vertices.at(model.GetFace(faces_c).GetVertexIndex(2)-1);

			//from 1x3 to 1x4
			glm::vec4 h1(p1, 1.0f);
			glm::vec4 h2(p2, 1.0f);
			glm::vec4 h3(p3, 1.0f);

			//transformations.
			h1 = translate_center * h1;
			h2 = translate_center * h2;
			h3 = translate_center * h3;
			
			//from 1x4 to 1x3
			
			//from 1x4 to 1x2
			glm::vec2 d1(h1.x, h1.y);
			glm::vec2 d2(h2.x, h2.y);
			glm::vec2 d3(h3.x, h3.y);
			DrawLine(d1,d2, glm::vec3(0.0f, 0.0f, 0.0f));
			DrawLine(d1,d3, glm::vec3(0.0f, 0.0f, 0.0f));
			DrawLine(d2,d3, glm::vec3(0.0f, 0.0f, 0.0f));
			
		}
	}
	
	/*******************************************************************/
	//int h1 = half_width;
	//int h2 = half_height;
	//int x = 0;
	//int y = 0; 
	//int R = Radius1;

	//draw line: from (0,0)to (half_width, half_height)...
	//DrawLine(glm::ivec2(0, 0),glm::ivec2(half_width, half_height),glm::vec3(1.0f, 0.0f,0.0f));
	
	//draw circle: from (half_width, half_height) to all directions ...
	//for (int i = 0; i < NDegrees; i++)
	//{
	//	x = half_width + Radius * cos(Teta*i);
	//	y = half_height + Radius * sin(Teta*i);
	//	DrawLine(glm::ivec2(half_width, half_height), glm::ivec2(x, y), glm::vec3(1.0f,0.0f,0.0f));
	//}

	//drawing of my own pic :
	//for (int i = 0; i < NDegrees/2; i++)
	//{
	//	x = h1 + Radius1 * cos(Teta*i);
	//	y = h2 + Radius1 * sin(Teta*i);
	//	R++;
	//	DrawLine(glm::ivec2(half_width, half_height), glm::ivec2(x, y), glm::vec3(1.0f,0.0f,0.0f));
	//}

	//for (int i = -10; i < NDegrees / 2; i++)
	//{
	//	x = half_width + Radius2 * cos(Teta*i);
	//	y = half_height + Radius2 * sin(Teta*i);
	//	R--;
	//	DrawLine(glm::ivec2(half_width - Radius1+200, half_height-300), glm::ivec2(x+100, y), glm::vec3(1.0f, 0.0f, 0.0f));
	//}
	//for (int i = 0; i < NDegrees / 2+10; i++)
	//{
	//	x = half_width + Radius2 * cos(Teta*i);
	//	y = half_height + Radius2 * sin(Teta*i);
	//	R--;
	//	DrawLine(glm::ivec2(half_width - Radius1+200 , half_height-300), glm::ivec2(x - 100, y), glm::vec3(1.0f, 0.0f, 0.0f));
	//}
	/*******************************************************************/
}

int Renderer::GetViewportWidth() const
{
	return viewport_width_;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height_;
}