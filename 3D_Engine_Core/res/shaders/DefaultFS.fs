#version 460

in vec2 fTexCoord;
in vec3 fNormal_eye;



#include <DirectionLight.glsl>
#include <PointLight.glsl>



struct Material
{
	bool hasDiffuseTexture;
	sampler2D diffuse_map;
	vec3 diffuse;

	bool hasSpecularTexture;
	sampler2D specular_map;
	float specular;
};



uniform DirectionLight light;
uniform Material material;



#define MAX_DIRECTION_LIGHTS 10
#define MAX_POINT_LIGHTS 10



struct SceneLight
{
	int direction_lights_amount;
	int point_lights_amount;

	DirectionLight direction_lights[MAX_DIRECTION_LIGHTS];
	PointLight point_lights[MAX_POINT_LIGHTS];
};



out vec4 frag_color;

void main() {

	vec3 color = material.diffuse;
	if (material.hasDiffuseTexture)
	{
		color = texture(material.diffuse_map, fTexCoord).rgb;
	}


	vec3 normal = normalize(fNormal_eye);

	vec3 direction_light = calcDirectionLights(light, normal, color);
	
	frag_color = vec4(direction_light, 1);
}