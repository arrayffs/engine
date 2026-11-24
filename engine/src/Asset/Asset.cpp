#include <Asset/Asset.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <filesystem>
#include <memory>

Asset::Asset()
{ }

void Asset::draw(glm::vec3 position)
{
  for (auto& mesh : _meshes)
    mesh.render();
}

Assimp::Importer importer;
Asset Asset::load_from_file(std::string filepath)
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

  std::vector<Mesh> meshes;
  std::pair<glm::vec3, glm::vec3> bounding_box;
  for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
    aiMesh* amesh = scene->mMeshes[i];

    //Material material(scene->mMaterials[amesh->mMaterialIndex]);
    //if (!material.diffuse_tex.empty())  material.diffuse_tex = directory + material.diffuse_tex;
    //if (!material.specular_tex.empty()) material.specular_tex = directory + material.specular_tex;
    //if (!material.normal_tex.empty())   material.normal_tex = directory + material.normal_tex;

    std::vector<vertex_t> vertices;
    vertices.reserve(amesh->mNumVertices);

    for (unsigned int j = 0; j < amesh->mNumVertices; ++j) {
      vertex_t v;

      v._world = { amesh->mVertices[j].x, amesh->mVertices[j].y, amesh->mVertices[j].z };
      if (amesh->HasNormals())
        v._normal = { amesh->mNormals[j].x, amesh->mNormals[j].y, amesh->mNormals[j].z };
      if (amesh->HasTextureCoords(0))
        v._tex = { amesh->mTextureCoords[0][j].x, amesh->mTextureCoords[0][j].y };

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

    //auto mesh = std::make_unique<Mesh>(ObjectType::MODEL, vertices, indices, *program, material, collider_surface);
    //if (collider_surface)
    //  CollisionRegistry::get_instance()->add_mesh(mesh.get());

    //meshes.push_back(std::move(mesh));
    meshes.push_back(Mesh(vertices, indices));
    if (i == 0) {
      bounding_box = meshes[0]._bounding_box;
    }
    else {
      auto& min = meshes[i]._bounding_box.first;
      auto& max = meshes[i]._bounding_box.first;

      if (bounding_box.first.x > min.x) bounding_box.first.x = min.x;
      if (bounding_box.first.y > min.y) bounding_box.first.y = min.y;
      if (bounding_box.first.z > min.z) bounding_box.first.z = min.z;

      if (bounding_box.second.x < max.x) bounding_box.second.x = max.x;
      if (bounding_box.second.y < max.y) bounding_box.second.y = max.y;
      if (bounding_box.second.z < max.z) bounding_box.second.z = max.z;
    }

    std::println("[?] Loaded mesh {}/{}", i + 1, scene->mNumMeshes);
  }

  Asset asset;
  asset._meshes = meshes;
  asset._bounding_box = bounding_box;
  
  return asset;
}
