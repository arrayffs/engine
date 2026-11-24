#version 330 core

in vec3 pass_frag;
in vec2 pass_texture;
in vec3 pass_normal;

out vec4 color;

vec3 hashColor(int id) {
    uint x = uint(id) + 1u;
    // Jenkins' one-at-a-time hash variant for good bit dispersion
    x += (x << 10u);
    x ^= (x >> 6u);
    x += (x << 3u);
    x ^= (x >> 11u);
    x += (x << 15u);
    
    // Extract 8-bit channels and normalize to [0.0, 1.0]
    float r = float((x & 0x000000FFu)) / 255.0;
    float g = float((x & 0x0000FF00u) >> 8u) / 255.0;
    float b = float((x & 0x00FF0000u) >> 16u) / 255.0;
    
    return vec3(r, g, b);
}

void main() {
  color = vec4(hashColor(gl_PrimitiveID), 1.0);
}