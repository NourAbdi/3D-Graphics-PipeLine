#version 330 core


struct Light{
	vec3 lightPos;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float ambientStr;
};

in vec2 texCoord;
in vec3 fragFinalPos;
in vec3 normalFinalPos;

uniform sampler2D texture;
uniform vec3 color;
uniform Light lighting;
uniform vec3 eyePos;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform float shine;
uniform bool toonShading;


out vec4 fColor;

void main() 
{ 
	//vec3 textureColor = vec3(texture(texture, texCoord));
	//Ambient light
	vec3 ambientlight = lighting.ambientColor * lighting.ambientStr * ambientColor; 

	//Diffuse light
	vec3 posToLightDirVec = normalize(lighting.lightPos - fragFinalPos);
	float diffuse = clamp(dot(posToLightDirVec,normalFinalPos),0,1);
	vec3 diffuseFinal = lighting.diffuseColor * diffuse * diffuseColor ;

	//Specular light
	vec3 reflectDirVec = normalize(reflect(posToLightDirVec,normalize(normalFinalPos)));
	vec3 posToViewDir = normalize( fragFinalPos - eyePos);
	float specularConstant = pow(max(dot(posToViewDir, reflectDirVec),0),10);
	vec3 specularFinal = lighting.specularColor * specularConstant * specularColor;
	if(toonShading){
		float intensity;
		vec4 ToonColor;
		intensity = dot(posToLightDirVec,normalFinalPos);

		if (intensity > 0.95)
			ToonColor = vec4(1.0,0.5,0.5,1.0);
		else if (intensity > 0.5)
			ToonColor = vec4(0.6,0.3,0.3,1.0);
		else if (intensity > 0.25)
			ToonColor = vec4(0.4,0.2,0.2,1.0);
		else
			ToonColor =vec4(0.2,0.1,0.1,1.0);
		fColor = vec4(color,1)*ToonColor;
	}else
   fColor = (vec4(ambientlight,1) + vec4(specularFinal,1) + vec4(diffuseFinal,1)) * vec4(color,1);
} 

