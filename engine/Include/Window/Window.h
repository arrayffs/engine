#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glm/glm.hpp>
#include <Utility/GLConfig.h>
//#include <imgui/imgui.h>

class Window
{
protected:
  GLFWwindow* _handle { nullptr };

  float _width  { 1800.f };
  float _height { 0900.f };
public:
  Window();

  bool should_close();

  void new_frame();
  void render();
  void poll_events();

  void set_cursor_lock(bool state);

  glm::vec2 calc_ndc();

  float width() const { return _width; }
  float height() const { return _height; }

  void set_key_callback(GLFWkeyfun key_callback);
  void set_cursor_pos_callback(GLFWcursorposfun cursor_position_callback);
  void set_mouse_button_callback(GLFWmousebuttonfun mouse_button_callback);
  void set_scroll_callback(GLFWscrollfun scroll_callback);
};

#endif // !_WINDOW_H_