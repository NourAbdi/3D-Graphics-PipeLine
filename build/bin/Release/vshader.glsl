#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 FragPos;
layout(location = 1) in vec3 FragNormal;
layout(location = 2) in vec2 texture;

out vec2 texCoord;
out vec3 fragFinalPos;
out vec3 normalFinalPos;

void main()
{

	//send to fragment shaders for phong shading.
	texCoord = texture;
	normalFinalPos = mat3(transpose(inverse(model))) * FragNormal;
	fragFinalPos = vec3( view * model* vec4( FragPos, 1 ) );

    gl_Position = projection * view * model * vec4(FragPos,1);
}
