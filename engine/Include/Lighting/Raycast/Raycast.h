#pragma once

#include <Utility/Singleton.h>
#include <GameWorld/BaseObject.h>

class Raycast
  : public Singleton<Raycast>
{
public:
  BaseObject* get_hovered_object(glm::vec2 ndc);
};