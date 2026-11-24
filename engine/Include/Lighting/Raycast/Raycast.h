#pragma once

#include <Utility/Singleton.h>
#include <BaseObject.h>

class Raycast
  : public Singleton<Raycast>
{
  BaseObject* get_hovered_object(glm::vec2 ndc);
};