#pragma once

namespace window {
  bool create_window();
  
  bool should_close();
  
  void newframe();
  void render();
  void poll_events();
  
  void set_cursor_lock(bool state);

  namespace properties {
    inline float width = 1800.f;
    inline float height = 900.f;
  }
}