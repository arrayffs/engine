#pragma once

#include "BaseObject.h"

class GameWorld
{
protected:
public:
  std::vector<BaseObject*> _objects;

  GameWorld() = default;
  ~GameWorld()
  {
    for (auto p : _objects)
      delete[] p;
  }

  void add_object(AssetIdentifier asset, glm::vec3 position)
  {
    BaseObject* object = new BaseObject(asset);
    object->set_position(position);

    _objects.push_back(object);
  }

  void remove_object(size_t idx)
  {
    delete[] _objects[idx];
    _objects.erase(_objects.begin() + idx);
  }
};