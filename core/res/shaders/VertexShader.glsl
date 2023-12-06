#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 texture_coords;

uniform mat4 model_view_matrix;
uniform mat3 normal_matrix;
uniform mat4 mvp_matrix;
uniform int current_frame;

out vec2 frag_texture_coord_smile;	
out vec2 frag_texture_coord_quads;	
out vec3 frag_normal_eye;	
out vec3 frag_position_eye;

void main() {
	frag_texture_coord_smile = texture_coords;
	frag_texture_coord_quads = texture_coords + vec2(current_frame / 1500.f, current_frame / 1500.f);
	
	frag_normal_eye = normal_matrix * vertex_normal;

	vec4 camera_vertex_position = model_view_matrix * vec4(vertex_position, 1.0);
	frag_position_eye = camera_vertex_position.xyz;
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}