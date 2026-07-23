#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Model.h"
#include "../Util/Singleton.h"

class AssetManager: public singleton<AssetManager>
{
private:
  std::vector<std::string> _available_assets{};

  std::vector<Model> _models{ };
  std::vector<Model> _debug_models{ };

  bool _lmb_down{ false };
  int _selected_model = { -1 };
public:
  AssetManager();
  
  bool load_asset(std::string asset_name);
  bool load_asset(std::vector<std::string> asset_names);

  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position);
  void poll();

  std::vector<std::string> get_available() const { return _available_assets; }
};

#endif // !_ASSET_MANAGER_H_