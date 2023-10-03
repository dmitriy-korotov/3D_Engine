#version 460

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 tex_coord;

uniform mat4 model_view_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

out vec2 fTexCoord;
out vec3 fNormal_eye;

void main() {
	fNormal_eye = normal_matrix * vertex_normal;
	fTexCoord = tex_coord;
	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
}