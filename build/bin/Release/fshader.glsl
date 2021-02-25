#version 330 core

struct Light{
	vec3 lightPos;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float ambientStr;
};

//in  vec2 texCoord;
in vec3 fragFinalPos;
in vec3 normalFinalPos;

//uniform sampler2D texture;
uniform vec3 color;
uniform Light lighting;
uniform vec3 eyePos;



out vec4 fColor;

void main() 
{ 
	//Ambient light
	vec3 ambientlight = lighting.ambientColor * lighting.ambientStr;

	//Diffuse light
	vec3 posToLightDirVec = normalize(lighting.lightPos - fragFinalPos);
	float diffuse = clamp(dot(posToLightDirVec,normalFinalPos),0,1);
	vec3 diffuseFinal = lighting.diffuseColor * diffuse ;

	//Specular light
	vec3 reflectDirVec = normalize(reflect(posToLightDirVec,normalize(normalFinalPos)));
	vec3 posToViewDir = normalize( fragFinalPos - eyePos);
	float specularConstant = pow(max(dot(posToViewDir, reflectDirVec),0),10);
	vec3 specularFinal = lighting.specularColor * specularConstant;

   fColor = (vec4(ambientlight,1) + vec4(specularFinal,1) + vec4(diffuseFinal,1)) * vec4(color,1);
} 

