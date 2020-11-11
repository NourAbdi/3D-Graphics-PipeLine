***Nour Abdi 20614750***

**1. Load a mesh and output it's vertices and face to the console (using cout) "demo model" :**
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
//I chose the 'demo' mish model to display :

![model's V F](https://user-images.githubusercontent.com/34486030/98798182-3e6ad000-2416-11eb-8186-52ebd1dd49c9.png)

**2. Scaling and translation the vertices such that they will fit inside the window (bunny for example) :**

