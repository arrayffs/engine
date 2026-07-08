#version 330 core

in vec3 pass_frag_pos;
in vec2 pass_tex_pos;
in vec3 pass_normal;

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
}; uniform Material u_material;

uniform vec3 u_light_color;
uniform vec3 u_light_source;
uniform vec3 u_camera_position;
uniform bool u_hovered;

out vec4 out_color;

void main() {
  float gamma = 2.2;

  // ambient
  vec3 ambient = u_material.ambient;

  // diffuse
  vec3 light_direction = normalize(u_light_source - pass_frag_pos);
  vec3 normal = normalize(pass_normal);
  
  float diff = max(dot(normal, light_direction), 0.0);
  vec3 diffuse = diff * u_material.diffuse;
  if (u_material.has_diffuse_tex) diffuse *= texture2D(u_material.diffuse_sampler, pass_tex_pos).rgb;

  // specular
  vec3 view_direction = normalize(u_camera_position - pass_frag_pos);
  vec3 halfway_direction = normalize(view_direction + light_direction);
  vec3 reflection_direction = reflect(-light_direction, normal);
  
  float spec = pow(max(dot(view_direction, halfway_direction), 0.0), u_material.shininess);
  vec3 specular = u_material.specular * spec * u_light_color;

  out_color = vec4(diffuse + specular, 1.f);

  if (u_hovered) {
    out_color.x += 0.05f;
    out_color.z += 0.05f;
  }

  // broken gamma correction!
  //out_color.rgb = pow(out_color.rgb, vec3(1.0 / gamma)); 
}