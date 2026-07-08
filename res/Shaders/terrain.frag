#version 330 core

in vec3 pass_frag_pos;
in vec2 pass_tex_pos;
in vec3 pass_normal;

out vec4 out_color;

void main()
{
	out_color = vec4(1.f, 1.f, 1.f, 1.f);
}