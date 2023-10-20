#version 460

in vec2 fTexCoord;
in vec3 fNormal_eye;



struct Material
{
	bool hasDiffuseTexture;
	sampler2D diffuse_map;
	vec3 diffuse;

	bool hasSpecularTexture;
	sampler2D specular_map;
	float specular;
};



uniform Material material;



out vec4 frag_color;

void main() {

	vec3 color = material.diffuse;
	if (material.hasDiffuseTexture)
	{
		color = texture(material.diffuse_map, fTexCoord).rgb;
	}

	frag_color = vec4(color, 1);
}