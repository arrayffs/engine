#include "Util/GLConfig.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <print>
#include "Terrain/Terrain.h"
#include "Keyboard/KeybindManager.h"
#include "Window/Window.h"
#include "Window/DebugWindow.h"

#include "Util/OrbitalCamera.h"
#include "AssetManager/Model.h"
#include "Raytracer/RaytracerThread.h"
#include "AssetManager/AssetManager.h"

int main(void)
{
  if (!window::create_window())
    return -1;

  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, -2.f, -5.f));
  glm::mat4 proj = glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 100.f);

  auto orbital_camera = OrbitalCamera::get_instance();
  orbital_camera->set_position({ 0.f, 10.f, 10.f });
  orbital_camera->set_pivot_point({ 0.f, 0.f, 0.f });

  glm::vec3 light_position = glm::vec3(5.f, 1.f, 1.f);
  RaytracerThread rt{ 100 };

  AssetManager asset_manager{ };
  asset_manager.load_asset(
    std::vector<std::string> {
      "pavement",
      "cube"
    }
  );

  Terrain terrain{ };
  terrain.generate(14124);

#ifdef _DEBUG
  debug_window::init();
#endif

  while (!window::should_close()) {
    window::newframe();
  
    keybind_manager::translate(model);
    view = orbital_camera->get_view();
    proj = glm::perspective(
      glm::radians(45.f),
      (float)window::properties::width / (float)window::properties::height,
      0.1f, 100.f
    );

    auto camera_position = orbital_camera->position();
    rt.update_view(model, view, proj, camera_position);

    asset_manager.render(model, view, proj, light_position, camera_position);
    terrain.render(model, view, proj, light_position, camera_position);
    
#ifdef _DEBUG
    debug_window::new_frame();

    ImGui::Begin("Test window");

    ImGui::SliderFloat("X", &light_position.x, -10.f, 10.f);
    ImGui::SliderFloat("Y", &light_position.y, -10.f, 10.f);
    ImGui::SliderFloat("Z", &light_position.z, -10.f, 10.f);
    ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());

    ImGui::End();

    debug_window::render();
#endif

    asset_manager.poll();
    window::render();
    window::poll_events();
  }

#ifdef _DEBUG
  debug_window::exit();
#endif

  glfwTerminate();
  return 0;
}
