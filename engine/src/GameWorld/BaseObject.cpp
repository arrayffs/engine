#include <GameWorld/BaseObject.h>
#include <Utility/GLConfig.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void BaseObject::render(int u_position)
{
  static AssetManager* asset_manager = AssetManager::inst();
  
  glUniform3fv(u_position, 1, glm::value_ptr(_position));
  if (auto* asset = asset_manager->get(_asset_id))
    asset->draw(_position);
}
