***Nour Abdi 206144750***

**Assignment2/part2 : displaying a shaded model**

**1.Implement the ability to add light sources to the scene, and apply transformations to
it. Your code should support point and parallel light sources. Reason about what trans-formations
make sense for each light source. Each light source must have three RGB components,
for the ambient, diffuse and specular reactions, so 9 values in total.**

![image](https://user-images.githubusercontent.com/34486030/104856340-ce4b5f80-591a-11eb-9950-532979b72bb0.png)
I chose the position to be the transformation for the point source of light :
![xzcasc](https://user-images.githubusercontent.com/34486030/104856513-c3dd9580-591b-11eb-9390-c9506c2bcc87.png)
I chose the direction to be the transformation for the parallel source of light :
![parallel](https://user-images.githubusercontent.com/34486030/104856514-c50ec280-591b-11eb-8b6a-c8d76f313710.png)
![sdfsdcs](https://user-images.githubusercontent.com/34486030/104856515-c50ec280-591b-11eb-83e1-103a79e18e91.png)
![sfvsdvsd](https://user-images.githubusercontent.com/34486030/104856516-c5a75900-591b-11eb-86c2-8f589038f9fd.png)
![fdsfsadfa](https://user-images.githubusercontent.com/34486030/104856600-48c8af00-591c-11eb-96aa-87d9852edf40.png)

**2.Allow the user to specify a material for each model. Similarly to light, each material
should have RGB values for ambient diffuse and specular re
ections.**

![dfsvdsv](https://user-images.githubusercontent.com/34486030/104856611-59792500-591c-11eb-84e7-a9cae9a5388a.png)

**3.Implement flat, Gouroad and Phong shading:**
Flat shading:
![flattt](https://user-images.githubusercontent.com/34486030/104856877-8548da80-591d-11eb-8238-28a3b6f99347.png)
Phong shading:
![Gouroud](https://user-images.githubusercontent.com/34486030/104856880-87129e00-591d-11eb-8bb8-71e74423fc86.png)
and Phong shading :
![Phong](https://user-images.githubusercontent.com/34486030/104856881-88dc6180-591d-11eb-9bc0-7511748e822c.png)

**4.Pick a model and clearly demonstrate that all of the lighting and shading capabilities
have been implemented. Add the relevant screenshots to the report and explain what is
shown in each picture.**

In this pictures the teapot model shows the diffrences between each lightining and shading method :

Flat shading:
![flattt](https://user-images.githubusercontent.com/34486030/104856877-8548da80-591d-11eb-8238-28a3b6f99347.png)
Phong shading:
![Gouroud](https://user-images.githubusercontent.com/34486030/104856880-87129e00-591d-11eb-8bb8-71e74423fc86.png)
and Phong shading :
![Phong](https://user-images.githubusercontent.com/34486030/104856881-88dc6180-591d-11eb-9bc0-7511748e822c.png)

**5.Implement the post-processing effects and demonstrate them.**

I chose to demonstrate the fog effects on the bunny :

the equation for the fog is :
f = (fog_end - Z) / (fog_end - fog_start);
Color = ((1 - f) * FogColor) + (f * color);

![dsfsdfc](https://user-images.githubusercontent.com/34486030/104857237-b924ff80-591f-11eb-8ae0-ee17f3bdf195.png)
![dfsgsfdgsa](https://user-images.githubusercontent.com/34486030/104857238-baeec300-591f-11eb-9718-e4fe3090236b.png)
