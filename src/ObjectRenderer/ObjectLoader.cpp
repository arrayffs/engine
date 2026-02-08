#include "ObjectLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>

namespace object_loader {
  Assimp::Importer importer;

  ObjectRenderer load_from_file(const std::string& filepath)
  {
    const aiScene* scene = importer.ReadFile(filepath,
      aiProcess_CalcTangentSpace |
      aiProcess_Triangulate |
      aiProcess_JoinIdenticalVertices |
      aiProcess_SortByPType
    );

    if (nullptr == scene) {
      std::println("Asset import failed: {}", importer.GetErrorString());
      return {};
    }


    std::vector<vertex_t> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < scene->mNumMeshes; ++i) {
      auto mesh = scene->mMeshes[i];

      for (auto j = 0; j < mesh->mNumVertices; ++j) {
        auto vertex = mesh->mVertices[j];
        //auto tex_coord = mesh->mTextureCoords[j];

        auto vertex_ = vertex_t{
          { vertex.x, vertex.y, vertex.z },
          { }
        };

        if (mesh->HasTextureCoords(0)) {
          auto& uv = mesh->mTextureCoords[0][j];
          vertex_._tex_pos = { uv.x, uv.y };
        }

        vertices.push_back(vertex_);
      }


      for (int j = 0; j < mesh->mNumFaces; ++j) {
        auto face = mesh->mFaces[j];
        for (auto k = 0; k < face.mNumIndices; ++k) {
          indices.push_back(face.mIndices[k]);
        }
      }
    }
    
    return ObjectRenderer(
      vertices, indices, "res/Shaders/monocolor_basic.vert", "res/Shaders/monocolor_basic.frag", "res/Textures/blue_ice.png"
    );
  }
}