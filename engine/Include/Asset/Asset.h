#ifndef _ASSET_H_
#define _ASSET_H_

#include <vector>
#include "Mesh.h"

class Asset
{
protected:
  std::vector<Mesh> _meshes{ };

public:

  Asset();
  void draw();
};

#endif // !_ASSET_H_