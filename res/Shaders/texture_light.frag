#version 330 core

in vec2 processed_tex_pos;

uniform sampler2D sampler;
uniform vec3 light_color;

out vec4 color;

void main() {
  color = texture2D(sampler, processed_tex_pos) * vec4(light_color, 1.0);
}