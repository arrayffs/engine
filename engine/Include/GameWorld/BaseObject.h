#pragma once

#include <Asset/AssetManager.h>

class BaseObject
{
protected:
  AssetIdentifier _asset_id{};
  glm::vec3 _position{  };

public:
  BaseObject(AssetIdentifier asset_id)
    :_asset_id(asset_id)
  {
    
  }


  void set_position(glm::vec3 position)
  {
    _position = position;
  }

  glm::vec3 get_position() const { return _position; }

  void render(int u_position);
  AssetIdentifier get_id() const { return _asset_id; }
};