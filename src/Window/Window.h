#pragma once

namespace window {
  bool create_window();
  
  bool should_close();
  
  void newframe();
  void render();
  void poll_events();
}