#pragma once

#include "Mesh.h"

class Model
{
protected:
  std::vector<std::unique_ptr<Mesh>> _meshes{ };
  bool _valid{ false };
public:
  Model() = default;
  Model(std::vector<std::unique_ptr<Mesh>> meshes);

  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position)
  {
    for (auto& mesh : _meshes)
      mesh->render(model, view, proj, light_source, position); 
  }

  static Model load_from_file(std::string filepath, std::string vs_path, std::string fs_path);
  bool is_valid() const { return _valid; }

  void set_pos(glm::vec3 pos)
  {
    for (auto& mesh : _meshes)
      mesh->set_pos(pos);
  }
};