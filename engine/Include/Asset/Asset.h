#ifndef _ASSET_H_
#define _ASSET_H_

#include <string>
#include <vector>
#include "Mesh.h"

class Asset
{
public:
  std::vector<Mesh> _meshes{ };
  std::pair<glm::vec3, glm::vec3> _bounding_box{ };

  Asset();
  void draw(glm::vec3 position);

  static Asset load_from_file(std::string path);
};

#endif // !_ASSET_H_