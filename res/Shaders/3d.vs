#version 330 core

layout(location = 0) in vec3 in_world;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texture;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

out vec3 pass_frag;
out vec2 pass_texture;
out vec3 pass_normal;

void main() {
	gl_Position = u_proj * u_view * u_model  * vec4(in_world/* + u_offset*/, 1.0);
  
  pass_frag = vec3(u_model * vec4(in_world, 1.0));
  pass_texture = in_texture;
  pass_normal = mat3(transpose(inverse(u_model))) * in_normal;
}