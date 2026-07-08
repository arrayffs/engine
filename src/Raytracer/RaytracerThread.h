#ifndef _RAYTRACER_THREAD_H_
#define _RAYTRACER_THREAD_H_

#include <thread>

#include "Raytracer.h"
#include "../Window/Window.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class RaytracerThread
{
private:
  std::thread _handle;
  bool _exitting{ false };

  glm::mat4 _model{}, _view{}, _proj{};
  glm::vec3 _camera_pos{};
public:
  RaytracerThread(int rt_rate) {

    _handle = std::thread([this, rt_rate]() {
      int frame{ 0 };
      auto* raytracer = Raytracer::get_instance();

      while (!_exitting) {
        if (frame % rt_rate == 0) {
          auto ndc = window::calc_ndc();
          glm::vec4 near_clip = glm::vec4(ndc.x, ndc.y, -1.f, 1.f);
          glm::vec4 far_clip = glm::vec4(ndc.x, ndc.y, 1.f, 1.f);
          glm::mat4 inverse_projection = glm::inverse(_proj * _view);

          glm::vec4 homogenous_near_ray = inverse_projection * near_clip;
          glm::vec4 homogenous_far_ray = inverse_projection * far_clip;

          glm::vec3 world_near_ray = glm::vec3(homogenous_near_ray) / homogenous_near_ray.w;
          glm::vec3 world_far_ray = glm::vec3(homogenous_far_ray) / homogenous_far_ray.w;

          glm::vec3 ray_direction = glm::normalize(world_far_ray - world_near_ray);

          raytracer->raycast(_camera_pos, ray_direction);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
  }

  ~RaytracerThread() {
    _exitting = true;
    _handle.join();
  }

  void update_view(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, glm::vec3& camera_position)
  {
    _model = model;
    _view = view;
    _proj = proj;
    _camera_pos = camera_position;
  }
};

#endif // !_RAYTRACER_THREAD_H_