#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#pragma once

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>

struct Material
{
  glm::vec3 diffuse = glm::vec3(1.f);
  glm::vec3 ambient = glm::vec3(0.f);
  glm::vec3 specular = glm::vec3(0.f);
  glm::vec3 emissive = glm::vec3(0.f);
  float shininess = 0.f;
  float opacity = 1.f;
  
  std::string diffuse_tex;
  std::string specular_tex;
  std::string normal_tex;

  Material() = default;
  Material(aiMaterial* mat)
  {
    aiColor3D c;
    aiString  path;

    if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, c) == AI_SUCCESS) diffuse = { c.r, c.g, c.b };
    if (mat->Get(AI_MATKEY_COLOR_AMBIENT, c) == AI_SUCCESS)
      ambient = glm::clamp(glm::vec3(c.r, c.g, c.b), glm::vec3(0.f), glm::vec3(0.2f));
    if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, c) == AI_SUCCESS) emissive = { c.r, c.g, c.b };

    mat->Get(AI_MATKEY_SHININESS, shininess);
    shininess = glm::max(shininess, 1.f);
    mat->Get(AI_MATKEY_OPACITY, opacity);

    if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
      diffuse_tex = path.C_Str();
      diffuse = glm::vec3(1.f);
    }
    else if (mat->GetTexture(aiTextureType_OPACITY, 0, &path) == AI_SUCCESS) {
      diffuse_tex = path.C_Str();
      diffuse = glm::vec3(1.f);
    } 

    if (mat->GetTexture(aiTextureType_SPECULAR, 0, &path) == AI_SUCCESS) {
      specular_tex = path.C_Str();
      specular = glm::vec3(1.f);
    }
    if (mat->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS) normal_tex = path.C_Str();

    if (normal_tex.empty() && 
      mat->GetTexture(aiTextureType_HEIGHT, 0, &path) == AI_SUCCESS) 
        normal_tex = path.C_Str();

    //dump();
  }

  // woah ai being useful?
  void dump(std::ostream& os = std::cout) const
  {
    os << std::fixed << std::setprecision(3);

    os << "Material {\n";
    os << "  diffuse      = (" << diffuse.x << ", " << diffuse.y << ", " << diffuse.z << ")\n";
    os << "  ambient      = (" << ambient.x << ", " << ambient.y << ", " << ambient.z << ")\n";
    os << "  specular     = (" << specular.x << ", " << specular.y << ", " << specular.z << ")\n";
    os << "  emissive     = (" << emissive.x << ", " << emissive.y << ", " << emissive.z << ")\n";
    os << "  shininess    = " << shininess << '\n';
    os << "  opacity      = " << opacity << '\n';
    os << "  diffuse_tex  = \"" << diffuse_tex << "\"\n";
    os << "  specular_tex = \"" << specular_tex << "\"\n";
    os << "  normal_tex   = \"" << normal_tex << "\"\n";
    os << "}\n";
  }


  Material(
    const glm::vec3& diffuse,
    const glm::vec3& ambient,
    const glm::vec3& specular,
    const glm::vec3& emissive,
    float shininess,
    float opacity,
    std::string diffuse_tex = {},
    std::string specular_tex = {},
    std::string normal_tex = {})
    : diffuse(diffuse),
    ambient(ambient),
    specular(specular),
    emissive(emissive),
    shininess(shininess),
    opacity(opacity),
    diffuse_tex(std::move(diffuse_tex)),
    specular_tex(std::move(specular_tex)),
    normal_tex(std::move(normal_tex))
  {
  }
};

#endif // !_MATERIAL_H_