#version 330 core

in vec2 processed_tex_pos;

uniform sampler2D sampler;

out vec4 color;

void main() {
  color = texture2D(sampler, processed_tex_pos);
}