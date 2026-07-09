#pragma once

#include "Mesh.h"

class Model
{
protected:
  bool _valid{ false };

  std::vector<std::unique_ptr<Mesh>> _meshes{ };

public:

  Model() = default;
  Model(std::vector<std::unique_ptr<Mesh>> meshes);

  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position)
  {
    for (auto& mesh : _meshes)
      mesh->render(model, view, proj, light_source, position); 
  }

  static Model load_from_file(std::string filepath, std::string vs_path, std::string fs_path, bool collider_surface = true);
  bool is_valid() const { return _valid; }

  void set_pos(glm::vec3 pos)
  {
    for (auto& mesh : _meshes)
      mesh->set_pos(pos);
  }

  glm::vec3 get_pos() const { return _meshes[0].get()->get_pos(); }


  void set_scale(glm::vec3 scale)
  {
    for (auto& mesh : _meshes)
      mesh->set_scale(scale);
  }

  glm::vec3 get_scale() const { return _meshes[0].get()->get_scale(); }

  bool is_hovered() {
    for (auto& mesh : _meshes)
      if (mesh->is_hovered())
        return true;

    return false;
  }
};