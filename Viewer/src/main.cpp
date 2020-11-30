#define _USE_MATH_DEFINES
#define pi  3.14159 
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>

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
glm::vec4 clear_color = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);

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

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
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
		//static bool test_window = FALSE;
		static float Lscale[] = { 0.0f, 0.0f };
		static float Lposition[] = { 0.0f, 0.0f };
		static float LAlpha_X = 0.0f;
		static float LAlpha_Y = 0.0f;
		static float LAlpha_Z = 0.0f;
		static float Wscale[] = { 0.0f, 0.0f };
		static float Wposition[] = { 0.0f, 0.0f };
		static float WAlpha_X = 0.0f;
		static float WAlpha_Y = 0.0f;
		static float WAlpha_Z = 0.0f;
		static glm::vec3 color( 0.0f, 0.0f, 0.0f);
		static glm::mat4 LScaling ;
		static glm::mat4 LTranslate ;
		static glm::mat4 LRotate ;
		static glm::mat4 WScaling ;
		static glm::mat4 WTranslate ;
		static glm::mat4 WRotate ;

		ImGui::Begin("Editor");     // Create a window called "Editor" and append into it.
		ImGui::Text("User Model control");

		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Local_Mode"))
			{
				mode = 0;
				ImGui::SliderFloat2("scale    (x,y)X(0~2)", Lscale, -1.0f, 1.0f);
				LScaling = {
					glm::vec4(Lscale[0] + 1,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,Lscale[1] + 1,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};

				ImGui::SliderFloat2("position (x+500,y+350)", Lposition, -1.0f, 1.0f);
				LTranslate = {
					glm::vec4(1.0f,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,1.0f,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(Lposition[0] * 500,Lposition[1] * 350,0.0f,1.0f)
				};

				ImGui::SliderFloat("X-rotation (0~2pi)", &LAlpha_X, 0, 2 * pi);
				ImGui::SliderFloat("Y-rotation (0~2pi)", &LAlpha_Y, 0, 2 * pi);
				ImGui::SliderFloat("Z-rotation (0~2pi)", &LAlpha_Z, 0, 2 * pi);
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
			if (ImGui::BeginTabItem("World_Mode"))
			{
				mode = 1;
				ImGui::SliderFloat2("scale    (x,y)X(0~2)", Wscale, -1.0f, 1.0f);
				WScaling = {
					glm::vec4(Wscale[0] + 1,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,Wscale[1] + 1,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(0.0f,0.0f,0.0f,1.0f)
				};

				ImGui::SliderFloat2("position (x+500,y+350)", Wposition, -1.0f, 1.0f);
				WTranslate = {
					glm::vec4(1.0f,0.0f,0.0f,0.0f),
					glm::vec4(0.0f,1.0f,0.0f,0.0f),
					glm::vec4(0.0f,0.0f,1.0f,0.0f),
					glm::vec4(Wposition[0] * 500,Wposition[1] * 350,0.0f,1.0f)
				};

				ImGui::SliderFloat("X-rotation (0~2pi)", &WAlpha_X, 0, 2 * pi);
				ImGui::SliderFloat("Y-rotation (0~2pi)", &WAlpha_Y, 0, 2 * pi);
				ImGui::SliderFloat("Z-rotation (0~2pi)", &WAlpha_Z, 0, 2 * pi);
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

			//ImGui::Checkbox("Bounding Box", &test_window);
			//if (test_window)
			//{
			//	model.
			//	//ImGui::Begin("Title bar Hovered/Active tests", &test_window);
			//	//if (ImGui::BeginPopupContextItem()) // <-- This is using IsItemHovered()
			//	//{
			//	//	if (ImGui::MenuItem("Close")) { test_window = false; }
			//	//	ImGui::EndPopup();
			//	//}
			//	//ImGui::Text(
			//	//	"IsItemHovered() after begin = %d (== is title bar hovered)\n"
			//	//	"IsItemActive() after begin = %d (== is window being clicked/moved)\n",
			//	//	ImGui::IsItemHovered(), ImGui::IsItemActive());
			//	ImGui::End();
			//}
		}

		ImGui::ColorEdit3("color", (float*)&color);

		if (scene.GetModelCount() > 0) //This check if we loaded the mesh model
		{
			MeshModel &model = scene.GetActiveModel(); // Gets active model
			model.SetLocalOrWorld(mode);
			model.SetColor(color);
			if (mode == 1)				// World mode
			{
				model.SetWTransform(WTranslate * WRotate * WScaling);
			}
			else if (mode == 0)		//Local mode
			{
				model.SetLTransform(LTranslate * LRotate * LScaling);
			}
			//model.SetBounding_Box(test_window);
		}
		ImGui::End();
	}
}