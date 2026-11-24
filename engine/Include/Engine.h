#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Utility/Singleton.h>
#include <Asset/AssetManager.h>
#include <GameWorld/GameWorld.h>
#include <Window/Window.h>
#include <Utility/Logger.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Engine
  : public Singleton<Engine>
{
protected:
  bool _running { false };
  AssetManager* _asset_manager  { AssetManager::inst() };
  Window _window  { };
  GameWorld _world  { };

  glm::mat4 _model = glm::mat4(1.f);
  glm::mat4 _view = glm::lookAt(
    glm::vec3(2.f, 2.f, 2.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 1.f, 0.f)
  );

  glm::mat4 _proj = glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 100.f);

public:
  glm::mat4& get_model()  { return _model; }
  glm::mat4& get_view()   { return _view; }
  const glm::mat4& get_proj()   const { return _proj; }
  
  Window* get_window_instance() { return &_window; }
  GameWorld* get_gameworld_instance() { return &_world; }

  void set_view(const glm::mat4& view) { _view = view; }
  void set_proj(const glm::mat4& proj) { _proj = proj; }

  bool init();
  bool shutdown();

  bool draw_frame();

  void set_key_callback(GLFWkeyfun key_callback) { _window.set_key_callback(key_callback); }
  void set_cursor_pos_callback(GLFWcursorposfun cursor_position_callback) { _window.set_cursor_pos_callback(cursor_position_callback); }
  void set_mouse_button_callback(GLFWmousebuttonfun mouse_button_callback) { _window.set_mouse_button_callback(mouse_button_callback); }
  void set_scroll_callback(GLFWscrollfun scroll_callback) { _window.set_scroll_callback(scroll_callback); }

};

#endif // !_ENGINE_H_