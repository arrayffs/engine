#include "KeybindManager.h"

#include <map>

typedef int Key;
std::map<Key, bool> g_keyboard;
std::map<Key, bool> g_queued_releases;

std::pair<Key, bool> g_mouse[5];
std::pair<Key, bool> g_queued_mouse[5];

void keybind_manager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (action)
  {
  case GLFW_PRESS:
    g_keyboard[key] = true;
    break;
  case GLFW_RELEASE:
    g_keyboard[key] = false;
  }
}

bool keybind_manager::key_down(int key)
{
  return g_keyboard[key];
}

bool keybind_manager::keypress(int key) {
  if (key_down(key)) {
    g_queued_releases[key] = true;
    return false;
  }

  bool state = g_queued_releases[key];
  g_queued_releases[key] = false;
  return state;
}