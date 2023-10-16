#version 460

in vec2 fTexCoord;
in vec3 fNormal_eye;

layout (binding = 0) uniform sampler2D inTexture;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
};

struct DirectionLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};






uniform DirectionLight light;




#define MAX_DIRECTION_LIGHTS 10
#define MAX_POINT_LIGHTS 10


vec3 calcDirectionLights(DirectionLight _light, vec3 _normal)
{
	vec3 ambient = _light.ambient * texture(inTexture, fTexCoord).rgb;
	
	float diff = max(dot(normalize(_light.direction), _normal), 0);
	vec3 diffuse = light.diffuse * diff * texture(inTexture, fTexCoord).rgb;

	// need specular

	return ambient + diffuse;
}


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