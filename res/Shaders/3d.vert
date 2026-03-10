#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_tex_pos;
layout(location = 2) in vec3 in_normal;

uniform vec3 u_offset;
uniform vec3 u_scale;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 pass_fragment_pos;
out vec2 pass_processed_tex_pos;
out vec3 pass_normal;

void main() {
	gl_Position = u_proj * u_view * u_model * vec4((in_pos + u_offset) * u_scale, 1.0);
	pass_fragment_pos = vec3(u_model * vec4((in_pos + u_offset) * u_scale, 1.0));

	pass_processed_tex_pos = in_tex_pos;
	pass_normal = in_normal;
}