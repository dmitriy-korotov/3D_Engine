#version 460

in vec2 frag_texture_coord_smile;
in vec2 frag_texture_coord_quads;
in vec3 frag_normal_eye;
in vec3 frag_position_eye;

layout (binding = 0) uniform sampler2D inTextureSmile;
layout (binding = 1) uniform sampler2D inTextureQuads;

uniform vec3 source_light_color;
uniform vec3 source_light_position;
uniform float ambient_factor;
uniform float diffuse_factor;
uniform float specular_factor;
uniform float shiniess;

out vec4 frag_color;

void main() {

	vec3 normal = normalize(frag_normal_eye);

	vec3 ambient_light = ambient_factor * source_light_color;
			
	vec3 light_direction = normalize(source_light_position - frag_position_eye);
	vec3 diffuse_light = diffuse_factor * source_light_color * max(dot(normal, light_direction), 0.0);

	vec3 reflect_dir = reflect(-light_direction, normal);
	vec3 direction_in_camera = normalize(-frag_position_eye);
	vec3 reflection_light = specular_factor * source_light_color * pow(max(dot(reflect_dir, direction_in_camera), 0.0), shiniess);


	vec4 light = vec4((ambient_light + diffuse_light + reflection_light), 1.f);
	frag_color = light * texture(inTextureSmile, frag_texture_coord_smile);//* texture(inTextureQuads, frag_texture_coord_quads);
}