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
```
Shader.use();
Shader.setUniform("model", modelMatrix);
Shader.setUniform("view", ViewMatrix);
Shader.setUniform("projection", Zooom * projection);
```

**4.Write a fragment shader that only outputs a constant color and paste it in the report.
The goal for now is to ensure that the pipeline works. Lights will be added later.**

Fragmant shader for constant color:

![51](https://user-images.githubusercontent.com/34486030/109212256-f64e9e00-77b7-11eb-9abe-b8e5355f72e9.jpeg)

**5.In the renderer, update all the relevant vertex attributes and uniforms, and paste the
relevant piece of code to the report. If everything was done correctly, you should be able
to view the mesh in your application.**

I chose the bishop model for demonstration :

![04](https://user-images.githubusercontent.com/34486030/109214891-10d64680-77bb-11eb-94cf-a10925db4587.jpeg)


