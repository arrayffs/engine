#version 330 core

in vec3 pass_frag_pos;
in vec2 pass_processed_tex_pos;
in vec3 pass_normal;

uniform sampler2D u_sampler;
uniform vec3 u_light_color;
uniform vec3 u_light_source;

out vec4 pass_color;

void main() {
  vec3 normal = normalize(pass_normal);
  vec3 light_direction = normalize(u_light_source - pass_frag_pos);

  pass_color = texture2D(u_sampler, pass_processed_tex_pos) * vec4(u_light_color, 1.0);
}