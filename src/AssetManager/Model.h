#pragma once

#include "../ObjectRenderer/ObjectRenderer.h"

class Model
{
protected:
  std::vector<Mesh> _meshes{ };
  bool _valid{ false };
public:
  Model() = default;
  Model(std::vector<Mesh> meshes);

  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj)
  {
    for (auto& mesh : _meshes)
      mesh.render(model, view, proj); 
  }

  static Model load_from_file(std::string filepath, std::string vs_path, std::string fs_path);
  bool is_valid() const { return _valid; }
};