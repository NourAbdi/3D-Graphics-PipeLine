***Nour Abdi 206144750***

****Assignment3 : OpenGL renderer****

**1.The software renderer was built on top of OpenGL. The Renderer::SwapBuffer() function
loads color buffer into a texture on the GPU. Read the function Renderer::InitOpenGLRendering()
and explain in the report how this texture is displayed. Remove all the now irrelevant
code from the renderer.**

**2.Update the MeshModel class to load the mesh on the GPU. Use the example OpenGL
project as a reference.**

![1](https://user-images.githubusercontent.com/34486030/109210620-c0a8b580-77b5-11eb-9102-c2ddadcb1217.jpeg)
![2](https://user-images.githubusercontent.com/34486030/109210621-c1414c00-77b5-11eb-9c50-b01ec3434e01.jpeg)
![3](https://user-images.githubusercontent.com/34486030/109210622-c2727900-77b5-11eb-90c0-7ea985ec7f0a.jpeg)
![4](https://user-images.githubusercontent.com/34486030/109210624-c30b0f80-77b5-11eb-9333-6c10b5ac1230.jpeg)

**3.Write a vertex shader that applies all the transformations. Use the reference code, but
pay attention to the differences between your code and the reference code. Copy the code
the the report.**

```
#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 FragPos;
layout(location = 1) in vec3 FragNormal;
layout(location = 2) in vec2 texture;

//out vec2 texCoord;
out vec3 fragFinalPos;

void main()
{
    gl_Position = vec3(projection * view * model * vec4(FragPos,1));
}
```

**4.Write a fragment shader that only outputs a constant color and paste it in the report.
The goal for now is to ensure that the pipeline works. Lights will be added later.**

Fragmant shader for constant color:

![51](https://user-images.githubusercontent.com/34486030/109212256-f64e9e00-77b7-11eb-9abe-b8e5355f72e9.jpeg)

**5.In the renderer, update all the relevant vertex attributes and uniforms, and paste the
relevant piece of code to the report. If everything was done correctly, you should be able
to view the mesh in your application.**

![4](https://user-images.githubusercontent.com/34486030/109210624-c30b0f80-77b5-11eb-9333-6c10b5ac1230.jpeg)

I chose the bishop model for demonstration :

```
Shader.use();
Shader.setUniform("model", modelMatrix);
Shader.setUniform("view", ViewMatrix);
Shader.setUniform("projection", Zooom * projection);
```

![04](https://user-images.githubusercontent.com/34486030/109214891-10d64680-77bb-11eb-94cf-a10925db4587.jpeg)


**6.Implement Phong shading in the fragment shader. To demonstrate that the performance
has now improved a lot, load one of the meshes from
https://github.com/alecjacobson/common-3d-test-models and display it from several view-
point and different lighting.**

![222](https://user-images.githubusercontent.com/34486030/109349223-47c16080-787e-11eb-93b1-ff2db7d308b3.png)
![dsfa](https://user-images.githubusercontent.com/34486030/109349228-48f28d80-787e-11eb-9f52-1284132c4b1f.png)
![safdsds](https://user-images.githubusercontent.com/34486030/109349232-4abc5100-787e-11eb-9724-57774488cd25.png)
![dasdsdsa](https://user-images.githubusercontent.com/34486030/109349235-4d1eab00-787e-11eb-85b4-0e1319f0bf4d.png)
![dsfsdfsdf](https://user-images.githubusercontent.com/34486030/109349242-4ee86e80-787e-11eb-84b6-b0f7621be652.png)

**7. Implement texture mapping. Use the example OpenGL project as reference. Enable
at least one type of canonical project (for pairs: three): plane, cylinder or sphere. In
addition, find a mesh with texture coordinates and use them. Show your results in the
report.**

I used the plane type of canonical project for example I used this texture :

![66](https://user-images.githubusercontent.com/34486030/109223079-cfe23000-77c2-11eb-994e-69b492710136.jpeg)

Using the wood texture on the crate :

![24](https://user-images.githubusercontent.com/34486030/109225046-6dd6fa00-77c5-11eb-934d-d708024b83e7.jpeg)

![25](https://user-images.githubusercontent.com/34486030/109223169-f0aa8580-77c2-11eb-84c7-64166a4a4faf.jpeg)

**8. Implementing (c) Toon shading (without the silhouette) :**

![28](https://user-images.githubusercontent.com/34486030/109345232-7fc5a500-7878-11eb-8427-36f4a6d347ca.jpeg)
