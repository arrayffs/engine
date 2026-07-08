#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "../Util/GLConfig.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>


namespace window {
  bool create_window();
  
  bool should_close();
  
  void newframe();
  void render();
  void poll_events();
  
  void set_cursor_lock(bool state);

  glm::vec2 calc_ndc();

  namespace properties {
    inline float width = 1800.f;
    inline float height = 900.f;

    inline GLFWwindow* _handle;
  }
}

#endif // !_WINDOW_H_