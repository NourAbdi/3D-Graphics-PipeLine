***Nour Abdi 206144750***

**Assignment3 : OpenGL renderer**

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

![11](https://user-images.githubusercontent.com/34486030/109211677-319c9d00-77b7-11eb-8ca0-45df435b0ad9.jpeg)

```
Shader.use();
Shader.setUniform("model", modelMatrix);
Shader.setUniform("view", ViewMatrix);
Shader.setUniform("projection", Zooom * projection);
```
