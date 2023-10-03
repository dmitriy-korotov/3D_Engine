#version 460

in vec2 fTexCoord;
in vec3 fNormal_eye;

layout (binding = 0) uniform sampler2D inTexture;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
};

struct Light
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;



out vec4 frag_color;

void main() {

	vec3 normal = normalize(fNormal_eye);

	
	
	vec3 ambient = light.ambient * texture(inTexture, fTexCoord).rgb;
	
	
	
	vec3 LightDir = normalize(-light.direction);
	float diff = max(dot(LightDir, normal), 0);
	vec3 diffuse = light.diffuse * texture(inTexture, fTexCoord).rgb;



	frag_color = vec4(ambient + diffuse, 1);
}