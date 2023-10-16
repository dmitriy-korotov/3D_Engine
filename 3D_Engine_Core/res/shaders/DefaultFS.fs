#version 460

in vec2 fTexCoord;
in vec3 fNormal_eye;

layout (binding = 0) uniform sampler2D inTexture;



#include <DirectionLight.glsl>
#include <PointLight.glsl>



struct Material
{
	sampler2D diffuse;
	sampler2D specular;
};



uniform DirectionLight light;



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

	vec3 normal = normalize(fNormal_eye);

	vec3 direction_light = calcDirectionLights(light, normal);
	
	frag_color = vec4(direction_light, 1);
}