#version 460

in vec2 fTexCoord;

layout (binding = 0) uniform sampler2D inTexture;

out vec4 frag_color;

void main() {
	frag_color = texture(inTexture, fTexCoord);
}