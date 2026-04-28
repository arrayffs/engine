#pragma once

#include <assimp/scene.h>
#include <glm/glm.hpp>

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
    if (mat->Get(AI_MATKEY_COLOR_AMBIENT, c) == AI_SUCCESS) ambient = { c.r, c.g, c.b };
    if (mat->Get(AI_MATKEY_COLOR_SPECULAR, c) == AI_SUCCESS) specular = { c.r, c.g, c.b };
    if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, c) == AI_SUCCESS) emissive = { c.r, c.g, c.b };

    mat->Get(AI_MATKEY_SHININESS, shininess);
    mat->Get(AI_MATKEY_OPACITY, opacity);

    if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) diffuse_tex = path.C_Str();
    if (mat->GetTexture(aiTextureType_SPECULAR, 0, &path) == AI_SUCCESS) specular_tex = path.C_Str();
    if (mat->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS) normal_tex = path.C_Str();

    if (normal_tex.empty() && 
      mat->GetTexture(aiTextureType_HEIGHT, 0, &path) == AI_SUCCESS) 
        normal_tex = path.C_Str();
  }
};