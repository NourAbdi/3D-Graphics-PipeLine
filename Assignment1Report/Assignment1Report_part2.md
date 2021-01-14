***Nour Abdi 206144750***

**Part 2 of the first assignment is to load a mesh, display it, and apply simple transformations
to it. The goal is to ensure that mesh transformation are correct before starting to implement
camera transformations.**

**1. Loading a mesh and outputing it's vertices and face to the console (using cout)
I chose the "demo model" to display it's vertices and face , Here is my implemintation for the code :**
```
//output model's vertices and faces :
//active model is the last opened file ( last read obj file)
int counterflag =0;
if (scene.GetModelCount() > 0) //this check if we loaded the mesh model
{
	MeshModel model = scene.GetActiveModel(); // gets active model 
	std::vector<glm::vec3> vertices = model.get_vertices(); // gets the vertices
	if (counterflag == 0)
	{
		for (int vertices_c = 0; vertices_c < vertices.size(); vertices_c++)
		{
			std::cout << "V" << vertices_c << ":";
			std::cout << " X=" << vertices[vertices_c].x ;
			std::cout << " , Y=" << vertices[vertices_c].y ;
			std::cout << " , Z=" << vertices[vertices_c].z << std::endl;
		}
		for (int faces_c = 0; faces_c < model.GetFacesCount(); faces_c++)
		{
		glm::vec3 p1 = vertices.at(model.GetFace(faces_c).GetVertexIndex(0)-1);
		glm::vec3 p2 = vertices.at(model.GetFace(faces_c).GetVertexIndex(1)-1);
		glm::vec3 p3 = vertices.at(model.GetFace(faces_c).GetVertexIndex(2)-1);

		std::cout << "F" << faces_c << ": ";
		std::cout <<"("<< p1.x << "," << p1.y << "," << p1.z << ")" << " , ";
		std::cout <<"("<< p2.x << "," << p2.y << "," << p2.z << ")" << " , ";
		std::cout <<"("<< p3.x << "," << p3.y << "," << p3.z << ")" << std::endl;
		}
	}
	counterflag++;
}
```
I chose the 'demo' mish model to display : Here is the output results using std::cout :

![model's V F](https://user-images.githubusercontent.com/34486030/98798182-3e6ad000-2416-11eb-8186-52ebd1dd49c9.png)

**2. Scaling and translation the vertices such that they will fit inside the window :
Scaling matrix is 4X4 all ondexes is 0.0f but the delta_x and the delta_y that we should calculate to fill in my window frame is neede
I calculate the rate between the window's frame and the mesh model frame to adjust the numbers for any mesh model ...**
```
void Renderer::Render(const Scene& scene)
{
	int half_width = viewport_width_ / 2;
	int half_height = viewport_height_ / 2;
	float Max = 0.0f;
	float Max_x = 0.0f;
	float Max_y = 0.0f;
	float Min_x = 0.0f;
	float Min_y = 0.0f;
	float max1	= 0.0f;
	float max2	= 0.0f;
	float Avg_x	= 0.0f;
	float Avg_y	= 0.0f;
	float delta_x = 0.0f;
	float delta_y = 0.0f;

	//Active model is the last opened file ( last read obj file)
	if (scene.GetModelCount() > 0) //This check if we loaded the mesh model
	{
		MeshModel model = scene.GetActiveModel(); // Gets active model 
		std::vector<glm::vec3> vertices = model.get_vertices(); // Gets the vertices

		//Drawing Axises :
		DrawLine(glm::vec2(0, half_height), glm::vec2(viewport_width_, half_height), glm::vec3(0.0f, 0.0f, 1.0f));
		DrawLine(glm::vec2(half_width, 0), glm::vec2(half_width, viewport_height_), glm::vec3(1.0f, 0.0f, 0.0f));

		//Check bounderies 0 < V < 1000
		for (int i = 0; i < vertices.size(); i++)
		{
			Max_x = (Max_x < vertices[i].x) ? vertices[i].x : Max_x;
			Max_y = (Max_y < vertices[i].y) ? vertices[i].y : Max_y;
			Min_y = (Min_y > vertices[i].y) ? vertices[i].y : Min_y;
			Min_x = (Min_x > vertices[i].x) ? vertices[i].x : Min_x;
		}
		Avg_x = (Max_x + Min_x) / 2;
		Avg_y = (Max_y + Min_y) / 2;
		max1 = (Max_x - Min_x);
		max2 = (Max_y - Min_y);
		Max = (max1 > max2) ? max1 : max2;
		delta_x = half_width / Max;
		delta_y = half_height / Max;
		Avg_x = Avg_x * delta_x;
		Avg_y = Avg_y * delta_y;

		glm::mat4 Translate_mat // Translation matrix to put the model in the right place
		(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(half_width- Avg_x, half_height- Avg_y, 0.0f, 1.0f)
		);
		glm::mat4 Scale_mat // Scaling matrix to adjust the size of the model
		(
			glm::vec4(delta_x, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, delta_y, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
		glm::mat4 Rotate_mat // Rotating matrix 
		(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
		glm::mat4 Final_mat = Translate_mat * Scale_mat * Rotate_mat;
	}
}
```

**3. From the Scene object, I transfered the mesh triangles to the Renderer object, iterated over
all of the triangles and drew all the lines using the DrawLine function, by ignoring one of
the coordinates. we are able to clearly view the object .
Here I put the blob model to show that the model is being viewed in the screen ,
later I will be able to translate it to the cinter of the screen:**

![blob mesh](https://user-images.githubusercontent.com/34486030/98930727-b0f6b100-24e5-11eb-8058-79d404309395.png)

**4. Create a GUI items to specify the local and world transformation that should be applied
to the model**
The GUI editor using one of two choices :
world and local transformations 
by choosing one of them the transformations matrix will deliver it to the model class :
Here is pictures for the GUI I created ...

![BananaImgui](https://user-images.githubusercontent.com/34486030/99217802-94a68d00-27e1-11eb-9617-46d95a06f6a5.png)

![bananana](https://user-images.githubusercontent.com/34486030/99251971-e4ec1200-2816-11eb-99e4-60a0801f472c.png)

**5.Show two screenshots comparing the difference between translating in the model frame and then
rotating in the world frame, vs. translating in the world frame and then rotating in the
local frame.**

translating in the model frame and then rotating in the world frame:

![11](https://user-images.githubusercontent.com/34486030/99251945-d867b980-2816-11eb-87e4-2d72be23c066.png)

vs. translating in the world frame and then rotating in the local frame

![222](https://user-images.githubusercontent.com/34486030/99252029-00571d00-2817-11eb-9be8-b85709e76bb5.png)






