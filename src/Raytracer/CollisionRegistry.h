#ifndef _COLLISION_REGISTRY_H_
#define _COLLISION_REGISTRY_H_

#include "../AssetManager/Mesh.h"
#include "../Util/Singleton.h"

#include <print>
#include <mutex>

class CollisionRegistry: public singleton<CollisionRegistry>
{
public:
  std::vector<Mesh*> _meshes;
  std::mutex _mesh_lock;

  void add_mesh(Mesh* mesh) { 
    std::lock_guard<std::mutex> lock(_mesh_lock);

    _meshes.push_back(mesh);
    std::println("[+] New collision mesh registered, current size {}", _meshes.size());
  }

  void remove_mesh(Mesh* mesh) {
    std::lock_guard<std::mutex> lock(_mesh_lock);

    std::erase(_meshes, mesh);
    std::println("[?] Collision mesh removed, current size {}", _meshes.size());
  }

};

#endif // !_COLLISION_REGISTRY_H_
