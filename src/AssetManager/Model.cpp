#include "Model.h"

#include "../Raytracer/CollisionRegistry.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <filesystem>

Model::Model(std::vector<std::unique_ptr<Mesh>> meshes)
  : _meshes(std::move(meshes))
{
  _valid = true;
}

Assimp::Importer importer;
Model Model::load_from_file(std::string filepath, std::string vs_path, std::string fs_path, bool collider_surface)
{
  importer.SetPropertyBool(AI_CONFIG_PP_FD_REMOVE, true);
  const aiScene* scene = importer.ReadFile(filepath,
    aiProcess_Triangulate |
    aiProcess_JoinIdenticalVertices |
    aiProcess_ImproveCacheLocality |
    aiProcess_RemoveRedundantMaterials |
    aiProcess_FlipUVs
  );

  if (nullptr == scene) {
    std::println("Asset import failed: {}", importer.GetErrorString());
    return {};
  }

  std::string directory = std::filesystem::path(filepath).parent_path().string() + "/";
  Program* program = new Program(vs_path, fs_path);

  std::vector<std::unique_ptr<Mesh>> meshes;
  for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
    aiMesh* amesh = scene->mMeshes[i];

    Material material(scene->mMaterials[amesh->mMaterialIndex]);
    if (!material.diffuse_tex.empty())  material.diffuse_tex = directory + material.diffuse_tex;
    if (!material.specular_tex.empty()) material.specular_tex = directory + material.specular_tex;
    if (!material.normal_tex.empty())   material.normal_tex = directory + material.normal_tex;

    std::vector<vertex_t> vertices;
    vertices.reserve(amesh->mNumVertices);

    for (unsigned int j = 0; j < amesh->mNumVertices; ++j) {
      vertex_t v;

      v._world_pos = { amesh->mVertices[j].x, amesh->mVertices[j].y, amesh->mVertices[j].z };
      if (amesh->HasNormals())
        v._normal = { amesh->mNormals[j].x, amesh->mNormals[j].y, amesh->mNormals[j].z };
      if (amesh->HasTextureCoords(0))
        v._tex_pos = { amesh->mTextureCoords[0][j].x, amesh->mTextureCoords[0][j].y };

      vertices.push_back(v);
    }

    std::vector<unsigned int> indices;
    indices.reserve(amesh->mNumFaces * 3);

    for (unsigned int j = 0; j < amesh->mNumFaces; ++j) {
      aiFace& face = amesh->mFaces[j];
      for (unsigned int k = 0; k < face.mNumIndices; ++k) {
        indices.push_back(face.mIndices[k]);
      }
    }

    auto mesh = std::make_unique<Mesh>(ObjectType::MODEL, vertices, indices, *program, material, collider_surface);
    if (collider_surface)
      CollisionRegistry::get_instance()->add_mesh(mesh.get());

    meshes.push_back(std::move(mesh));


    std::println("[?] Loaded mesh {}/{}", i + 1, scene->mNumMeshes);
  }

  return Model(std::move(meshes));
}
