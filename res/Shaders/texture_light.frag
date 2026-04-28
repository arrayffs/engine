#version 330 core

in vec3 pass_frag_pos;
in vec2 pass_processed_tex_pos;
in vec3 pass_normal;

uniform sampler2D u_sampler;
uniform vec3 u_light_color;
uniform vec3 u_light_source;

struct Material {
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
    float opacity;

    bool has_diffuse_tex;
    sampler2D diffuse_sampler;

    bool has_specular_tex;
    sampler2D specular_sampler;

    bool has_normal_tex;
    sampler2D normal_sampler;
};

uniform Material u_material;

out vec4 pass_color;

void main() {
  vec3 normal = normalize(pass_normal);
  vec3 light_direction = normalize(u_light_source - pass_frag_pos);

  //pass_color = texture2D(u_material., pass_processed_tex_pos);// * vec4(u_light_color, 1.0);

  pass_color = vec4(u_material.diffuse * u_material.ambient * u_material.specular  * u_material.opacity, 1.f);
  if (u_material.has_diffuse_tex)
    pass_color *= texture2D(u_material.diffuse_sampler, pass_processed_tex_pos);
  if (u_material.has_specular_tex)
    pass_color *= texture2D(u_material.specular_sampler, pass_processed_tex_pos);
  if (u_material.has_normal_tex)
    pass_color *= texture2D(u_material.normal_sampler, pass_processed_tex_pos);
}