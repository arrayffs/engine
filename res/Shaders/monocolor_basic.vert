#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 processed_tex_pos;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);
	processed_tex_pos = tex_pos;
}