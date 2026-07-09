#include "AssetManager.h"
#include "../Keyboard/KeybindManager.h"

#define DEBUG_ASSET_ARROW 0

AssetManager::AssetManager()
{
  _debug_models.push_back(Model::load_from_file(
    "res/Models/arrow.obj",
    "res/Shaders/3d.vert",
    "res/Shaders/white.frag"
  ));
}

bool AssetManager::load_asset(std::string asset_name)
{
  _models.push_back(Model::load_from_file(
    std::format("res/Models/{}.obj", asset_name),
    "res/Shaders/3d.vert",
    "res/Shaders/texture_light.frag"
  ));

  return true;
}

bool AssetManager::load_asset(std::vector<std::string> asset_names)
{
  for (auto name : asset_names) {
    if (!load_asset(name)) return false;
  }

  return true;
}

void AssetManager::render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position)
{
  for (int i = 0; i < _models.size(); ++i) {
    auto& asset = _models[i];

    asset.render(model, view, proj, light_source, position);
  }

  if (_selected_model < 0) return;

  auto& asset = _models[_selected_model];
  
  _debug_models[DEBUG_ASSET_ARROW].set_pos(asset.get_pos() + glm::vec3(0.f, 2.f, 0.f));
  _debug_models[DEBUG_ASSET_ARROW].set_scale(glm::vec3(0.2f, 0.2f, 0.2f);
  _debug_models[DEBUG_ASSET_ARROW].render(model, view, proj, light_source, position);
}

void AssetManager::poll()
{
  if (keybind_manager::lmb_down()) {
    if (!_lmb_down) _lmb_down = true;
    else {
      for (int i = 0; i < _models.size(); ++i) {
        if (_models[i].is_hovered())
          _selected_model = i;
      }
    }
  }
  else _lmb_down = false;

  if (keybind_manager::key_down(GLFW_KEY_ESCAPE))
    _selected_model = -1;
}
