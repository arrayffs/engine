#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Utility/Singleton.h>
#include <Asset/AssetManager.h>
#include <Window/Window.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Engine
  : public Singleton<Engine>
{
protected:
  bool _running { false };
  AssetManager* _asset_manager  { AssetManager::inst() };
  Window _window  { };

  glm::mat4 _model = glm::mat4(1.f);
  glm::mat4 _view = glm::lookAt(
    glm::vec3(2.f, 2.f, 2.f),
    glm::vec3(0.f, 0.f, 0.f),
    glm::vec3(0.f, 1.f, 0.f)
  );

  glm::mat4 _proj = glm::perspective(glm::radians(45.f), 16.f / 9.f, 0.1f, 100.f);

public:
  bool init();
  bool shutdown();

  bool draw_frame();
};

#endif // !_ENGINE_H_