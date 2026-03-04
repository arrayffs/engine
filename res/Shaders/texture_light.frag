#version 330 core

in vec3 in_frag_pos;
in vec2 in_processed_tex_pos;
in vec3 in_normal;

uniform sampler2D u_sampler;
uniform vec3 u_light_color;
uniform vec3 u_light_source;

out vec4 out_color;

void main() {
  vec3 normal = normalize(in_normal);
  vec3 light_direction = normalize(u_light_source - in_frag_pos);

  out_color = texture2D(u_sampler, in_processed_tex_pos) * vec4(u_light_color, 1.0);
}