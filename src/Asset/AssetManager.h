#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <utility>
#include <memory>
#include <optional>
#include <string>

#include "Asset.h"
#include <Utility/Singleton.h>

#define MAX_ASSETS 25565

class AssetManager:
  public Singleton<AssetManager>
{
private:
  std::vector<std::shared_ptr<Asset>> _assets{ };
public:
  std::pair<std::shared_ptr<Asset>, size_t> load_asset(std::string asset_name)
  {
    auto ptr = std::make_shared<Asset>(Asset());
    _assets.push_back(ptr);
    
    return std::pair {
      ptr, _assets.size() - 1
    };
  }

  std::shared_ptr<Asset> get(size_t idx) const { return _assets[idx]; }
};

#endif // !_ASSET_MANAGER_H_