#define _USE_MATH_DEFINES
#define Pi  3.14159 
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include <memory>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"

/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
static glm::vec3 black(0.0f, 0.0f, 0.0f);
static glm::vec3 white(1.0f, 1.0f, 1.0f);
glm::vec4 clear_color = glm::vec4(0.6f, 0.6f, 0.6f, 1.00f);

/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);

/**
 * Function implementation
 */

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char **argv)
{
	int windowWidth = 1280, windowHeight = 720;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;


	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glEnable(GL_DEPTH_TEST);

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer(frameBufferWidth, frameBufferHeight);
	renderer.LoadShaders();
	renderer.LoadTextures();
	Scene scene = Scene();
	
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene);
		RenderFrame(window, scene, renderer, io);
    }

	Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
		//renderer.SetViewportWidth(frameBufferWidth);
		//renderer.SetViewportHeight(frameBufferHeight);
		renderer.ResizeBuffers(frameBufferWidth, frameBufferHeight);
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	renderer.SwapBuffers();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");
	
	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed
	
	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	//Editor window :
	{
		static int mode = 0;
		static int ONCE = 0;
		static int ONCEE = 0;
		static bool BoundingBox = FALSE;
		static bool FacesNormals = FALSE;
		static bool VerticesNormals = FALSE;
		static bool Proj_or_Ortho = FALSE;
		static bool PointOrParallel = FALSE;
		static float Lscale[] = { 0.0f, 0.0f, 0.0f };
		static float Lposition[] = { 0.0f, 0.0f, 0.0f };
		static float LAlpha_X = 0.0f;
		static float LAlpha_Y = 0.0f;
		static float LAlpha_Z = 0.0f;
		static float Wscale[] = { 0.0f, 0.0f, 0.0f };
		static float Wposition[] = { 0.0f, 0.0f, 0.0f };
		static float WAlpha_X = 0.0f;
		static float WAlpha_Y = 0.0f;
		static float WAlpha_Z = 0.0f;
		static glm::vec3 color( 0.8f, 0.8f, 0.8f);
		static glm::vec3 ambient_color(1.0f, 1.0f, 1.0f);
		static glm::vec3 diffuse_color(1.0f, 1.0f, 1.0f);
		static glm::vec3 specular_color(1.0f, 1.0f, 1.0f);
		static glm::vec3 ambient_light(1.0f, 1.0f, 1.0f);
		static glm::vec3 diffuse_light(1.0f, 1.0f, 1.0f);
		static glm::vec3 specular_light(1.0f, 1.0f, 1.0f);
		static glm::vec3 FogColor(0.6f,0.6f,0.6f);
		static float ambient_light_intensity = 0.1f;
		static float fogStart = 98.0f;
		static float fogEnd = 100.0f;
		static glm::mat4 LScaling ;
		static glm::mat4 LTranslate ;
		static glm::mat4 LRotate ;
		static glm::mat4 WScaling ;
		static glm::mat4 WTranslate ;
		static glm::mat4 WRotate ;
		static glm::mat4 CRotate ;
		static glm::mat4 LLRotate ;
		static float  l = -1.0f, r = 1.0f, b = -1.0f, t = 1.0f;
		static float  fovy = 1.0f, nearP = -1.0f, farP = -10.0f;
		static float Cposition[] = { 0.0f, 0.0f, 300.0f };
		static float LLposition[] = { 0.0f, 0.0f, 100.0f };
		static float Ldirection[] = { 0.0f, 0.0f, -1.0f };
		static float Zoom = 0.2f;
		static float CAlpha_X = 0.0f;
		static float CAlpha_Y = 0.0f;
		static float CAlpha_Z = 0.0f;
		static float LLAlpha_X = 0.0f;
		static float LLAlpha_Y = 0.0f;
		static float LLAlpha_Z = 0.0f;
		static glm::mat4 CTranslate;
		static glm::mat4 LLTranslate;
		
		ImGui::Begin("Model Control");     // Create a window called "Model Control" and append into it.
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Model Frame"))
			{
				mode = 0;
				ImGui::SliderFloat2("scale (x,y)X(0~2)", Lscale, -1.0f, 1.0f);
				LScaling = {
					glm::vec4(Lscale[0] + 1,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,Lscale[1] + 1,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1,0.0f),
					glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};

				ImGui::SliderFloat3("position (x,y,z)", Lposition, -1.0f, 1.0f);
				LTranslate = {
					glm::vec4(1.0f,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,1.0f,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(Lposition[0]*10 ,Lposition[1]*10 ,Lposition[2],1.0f)
				};

				ImGui::SliderFloat("X-rotation (0~2pi)", &LAlpha_X, 0, 2 * Pi);
				ImGui::SliderFloat("Y-rotation (0~2pi)", &LAlpha_Y, 0, 2 * Pi);
				ImGui::SliderFloat("Z-rotation (0~2pi)", &LAlpha_Z, 0, 2 * Pi);
				glm::mat4 Rotate_X = {
				glm::vec4(1.0f,0.0f,0.0f,0.0f),
				glm::vec4(0.0f,cos(LAlpha_X),sin(LAlpha_X),0.0f),
				glm::vec4(0.0f,-sin(LAlpha_X),cos(LAlpha_X),0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				glm::mat4 Rotate_Y = {
				glm::vec4(cos(LAlpha_Y),0.0f,sin(LAlpha_Y),0.0f),
				glm::vec4(0.0f,1.0f,0.0f,0.0f),
				glm::vec4(-sin(LAlpha_Y),0.0f,cos(LAlpha_Y),0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				glm::mat4 Rotate_Z = {
				glm::vec4(cos(LAlpha_Z),sin(LAlpha_Z),0.0f,0.0f),
				glm::vec4(-sin(LAlpha_Z),cos(LAlpha_Z),0.0f,0.0f),
				glm::vec4(0.0f,0.0f,1.0f,0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				LRotate = Rotate_Z * Rotate_Y * Rotate_X; 
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("World Frame"))
			{
				mode = 1;
				ImGui::SliderFloat2("scale (x,y)X(0~2)", Wscale, -1.0f, 1.0f);
				WScaling = {
					glm::vec4(Wscale[0] + 1,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,Wscale[1] + 1,0.0f,0.0f),
					glm::vec4(0.0f,0.0f, 1,0.0f),
					glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};

				ImGui::SliderFloat3("position (x,y,z)", Wposition, -1.0f, 1.0f);
				WTranslate = {
					glm::vec4(1.0f,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,1.0f,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(Wposition[0] ,Wposition[1] ,Wposition[2],1.0f)
				};

				ImGui::SliderFloat("X-rotation (0~2pi)", &WAlpha_X, 0, 2 * Pi);
				ImGui::SliderFloat("Y-rotation (0~2pi)", &WAlpha_Y, 0, 2 * Pi);
				ImGui::SliderFloat("Z-rotation (0~2pi)", &WAlpha_Z, 0, 2 * Pi);
				glm::mat4 Rotate_X = {
				glm::vec4(1.0f,0.0f,0.0f,0.0f),
				glm::vec4(0.0f,cos(WAlpha_X),sin(WAlpha_X),0.0f),
				glm::vec4(0.0f,-sin(WAlpha_X),cos(WAlpha_X),0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				glm::mat4 Rotate_Y = {
				glm::vec4(cos(WAlpha_Y),0.0f,sin(WAlpha_Y),0.0f),
				glm::vec4(0.0f,1.0f,0.0f,0.0f),
				glm::vec4(-sin(WAlpha_Y),0.0f,cos(WAlpha_Y),0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				glm::mat4 Rotate_Z = {
				glm::vec4(cos(WAlpha_Z),sin(WAlpha_Z),0.0f,0.0f),
				glm::vec4(-sin(WAlpha_Z),cos(WAlpha_Z),0.0f,0.0f),
				glm::vec4(0.0f,0.0f,1.0f,0.0f),
				glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};
				WRotate = Rotate_Z * Rotate_Y * Rotate_X; ;
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();

			ImGui::Checkbox("Bounding Box", &BoundingBox);
			ImGui::Checkbox("Faces Normals", &FacesNormals);
			ImGui::Checkbox("Vertices Normals", &VerticesNormals);
		}
		ImGui::ColorEdit3("Model Color", (float*)&color);
		ImGui::ColorEdit3("Ambient Color", (float*)&ambient_color);
		ImGui::ColorEdit3("Diffuse Color", (float*)&diffuse_color);
		ImGui::ColorEdit3("Specular Color", (float*)&specular_color);
		ImGui::End();
		/***********************************************************************************************************/
		ImGui::Begin("Camera Control");     // Create a window called "Model Control" and append into it.
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Orthographic"))
			{
				Proj_or_Ortho = false;
				ImGui::SliderFloat("left", &l, -5.0f, 5.0f);
				ImGui::SliderFloat("right", &r, -5.0f, 5.0f);
				ImGui::SliderFloat("bottom", &b, -5.0f, 5.0f);
				ImGui::SliderFloat("top", &t, -5.0f, 5.0f);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Perspective"))
			{
				Proj_or_Ortho = true;
				ImGui::SliderFloat("fovy", &fovy, -2.0f, 2.0f);
				ImGui::SliderFloat("near", &nearP, 0.0f, 5.0f);
				ImGui::SliderFloat("far", &farP, 0.0f, 100.0f);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::SliderFloat3("position(x,y,z)", Cposition, -1000.0f, 1000.0f);
		CTranslate = {
			glm::vec4(1.0f,0.0f,0.0f,0.0f),
			glm::vec4(0.0f,1.0f,0.0f,0.0f),
			glm::vec4(0.0f,0.0f,1.0f,0.0f),
			glm::vec4(Cposition[0],Cposition[1] ,Cposition[2],1.0f)
		};
		ImGui::SliderFloat("Zoom", &Zoom, -2.0f, 5.0f);
		ImGui::SliderFloat("X-rotation (0~2pi)", &CAlpha_X, 0, 2 * Pi);
		ImGui::SliderFloat("Y-rotation (0~2pi)", &CAlpha_Y, 0, 2 * Pi);
		ImGui::SliderFloat("Z-rotation (0~2pi)", &CAlpha_Z, 0, 2 * Pi);
		glm::mat4 Rotate_X = {
		glm::vec4(1.0f,0.0f,0.0f,0.0f),
		glm::vec4(0.0f,cos(CAlpha_X),sin(CAlpha_X),0.0f),
		glm::vec4(0.0f,-sin(CAlpha_X),cos(CAlpha_X),0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
		};
  		glm::mat4 Rotate_Y = {
		glm::vec4(cos(CAlpha_Y),0.0f,sin(CAlpha_Y),0.0f),
		glm::vec4(0.0f,1.0f,0.0f,0.0f),
		glm::vec4(-sin(CAlpha_Y),0.0f,cos(CAlpha_Y),0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
		};
		glm::mat4 Rotate_Z = {
		glm::vec4(cos(CAlpha_Z),sin(CAlpha_Z),0.0f,0.0f),
		glm::vec4(-sin(CAlpha_Z),cos(CAlpha_Z),0.0f,0.0f),
		glm::vec4(0.0f,0.0f,1.0f,0.0f),
		glm::vec4(0.0f,0.0f,0.0f,1.0f)
		};
		CRotate = Rotate_Z * Rotate_Y * Rotate_X;
		ImGui::End();
		/***********************************************************************************************************/
		ImGui::Begin("Light Source Control");     // Create a window called "Light Source Control" and append into it.
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Point"))
			{
				PointOrParallel = true;
				//ImGui::InputFloat3("position (x,y,z)", LLposition);
				ImGui::SliderFloat3("position (x,y,z)", LLposition,-100.0f,100.0f);
				LLTranslate = {
					glm::vec4(1.0f,0.0f,0.0f,0.0f),		
					glm::vec4(0.0f,1.0f,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(LLposition[0],LLposition[1] ,LLposition[2],1.0f)
				};
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Parallel"))
			{
				PointOrParallel = false;
				ImGui::SliderFloat3("direction ->(x,y,z)", Ldirection, -1.0f, 1.0f);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::ColorEdit3("ambient light ", (float*)&ambient_light);
		ImGui::SliderFloat("ambient intensity", &ambient_light_intensity,0.0f,1.0f);
		ImGui::ColorEdit3("diffuse light ", (float*)&diffuse_light);
		ImGui::ColorEdit3("specular light ", (float*)&specular_light); 
		//ImGui::SliderFloat("ambient intensity", &shininess ,0.0f, 100.0f);

		ImGui::Text("shading :  "); ImGui::SameLine();
		static int e = 0;
		ImGui::RadioButton("Flat", &e, 0); ImGui::SameLine();
		ImGui::RadioButton("Gouraud", &e, 1); ImGui::SameLine();
		ImGui::RadioButton("Phong", &e, 2);

		static bool Fog = false;
		ImGui::Checkbox("Enable Fog", &Fog);
		ImGui::ColorEdit3("Fog color ", (float*)&FogColor);
		ImGui::SliderFloat("fog Start", &fogStart, 95.0f, 100.0f);
		ImGui::SliderFloat("fog End", &fogEnd, 98.0f, 105.0f);
		/*********************************************************************************************************/
		if (!ONCE)
		{
			std::shared_ptr<Camera> camera = std::make_shared<Camera>();
			scene.AddCamera(camera);
			ONCE++;
		}
		if (scene.GetCameraCount() > 0) //This check if we loaded a camera
		{
			Camera &camera = scene.GetActiveCamera();
			camera.SetOrthoOrProj(Proj_or_Ortho);
			camera.SetZoom(Zoom);
			camera.SetViewTransformation(CRotate);
			camera.SetCameraPosition(glm::vec3(Cposition[0], Cposition[1], Cposition[2]));
			if (!Proj_or_Ortho)
			{
				camera.SetProjectionTransformation(glm::ortho(l, r, b, t));
			}
			if (Proj_or_Ortho)
			{
				camera.Setfovy(fovy);
				camera.Setnear(nearP);
				camera.Setfar(farP);
			}
		}
		/*********************************************************************************************************/
		if (!ONCEE)
		{
			std::shared_ptr<Light> light = std::make_shared<Light>();
			scene.AddLight(light);
			ONCEE++;
		}
		if (scene.GetLightCount() > 0) //This check if we loaded a camera
		{
			Light &light = scene.GetActiveLight();
			light.SetPointOrParallel(PointOrParallel);
			//light.SetTransformation(LLRotate*LLTranslate);
			light.SetPosition(glm::vec3(LLposition[0], LLposition[1], LLposition[2]));
			light.SetDirection(glm::vec3(Ldirection[0], Ldirection[1], Ldirection[2]));
			light.Setambient(ambient_light);
			light.Setambientintensity(ambient_light_intensity);
			light.Setdiffuse(diffuse_light);
			light.Setspecular(specular_light);
			//light.Setshininess(shininess);
			light.Setshading_kind(e);
			light.SetFog(Fog);
			light.SetfogStart(fogStart);
			light.SetfogEnd(fogEnd);
			light.SetFogColor(FogColor);
		}
		/***********************************************************************************************************/
		if (scene.GetModelCount() > 0) //This check if we loaded the mesh model
		{
			MeshModel &model = scene.GetActiveModel(); // Gets active model
			model.SetLocalOrWorld(mode);
			model.SetColor(color);
			model.Setambient(ambient_color);
			model.Setdiffuse(diffuse_color);
			model.Setspecular(specular_color);
			if (mode == 1)				// World mode
			{
				model.SetWTransform(WTranslate * WRotate * WScaling);
			}
			if (mode == 0)		//Local mode
			{
				model.SetLTransform(LTranslate * LRotate * LScaling);
			}
			model.Setbounding_box(BoundingBox);
			model.Setfaces_normals(FacesNormals);
			model.Setvertices_normals(VerticesNormals);

		}
		ImGui::End();
	}
}