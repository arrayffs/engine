#include <Lighting/Raycast/Raycast.h>
#include <GameWorld/GameWorld.h>
#include <Engine.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/component_wise.hpp>

BaseObject* Raycast::get_hovered_object(glm::vec2 ndc)
{
  glm::vec4 near_clip(ndc.x, ndc.y, -1.f, 1.f);
  glm::vec4 far_clip(ndc.x, ndc.y, 1.f, 1.f);

  static auto* engine = Engine::inst();
  static auto* world = engine->get_gameworld_instance();
  static auto* asset_manager = AssetManager::inst();

  glm::mat4 inv = glm::inverse(engine->get_proj() * engine->get_view());
  glm::vec4 n = inv * near_clip;
  glm::vec4 f = inv * far_clip;

  n /= n.w;
  f /= f.w;

  glm::vec3 origin = glm::vec3(n);
  glm::vec3 inv_dir = 1.f / glm::normalize(glm::vec3(f - n));

  BaseObject* closest{ nullptr };
  float closest_t{ std::numeric_limits<float>::max() };
  for (auto object : world->_objects) {
    Asset* asset = asset_manager->get(object->get_id());
    glm::vec3 box_min = asset->_bounding_box.first;
    glm::vec3 box_max = asset->_bounding_box.second;
    glm::vec3 position = object->get_position();

    glm::vec3 t1 = (asset->_bounding_box.first + position - origin) * inv_dir;
    glm::vec3 t2 = (asset->_bounding_box.second + position - origin) * inv_dir;

    float t_enter = glm::compMax(glm::min(t1, t2));
    float t_exit = glm::compMin(glm::max(t1, t2));

    if (t_enter > t_exit || t_exit < 0.f) continue;

    float t_hit = t_enter >= 0.f ? t_enter : t_exit;
    if (t_hit < closest_t) {
      closest_t = t_hit;
      closest = object;
    }
  }

  return closest;
}