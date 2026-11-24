#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <utility>
#include <memory>
#include <optional>
#include <string>

#include "Asset.h"
#include <Utility/Singleton.h>

typedef size_t AssetIdentifier;

class AssetManager
  : public Singleton<AssetManager>
{
private:
  std::vector<std::unique_ptr<Asset>> _assets{ };
  std::unordered_map<std::string, AssetIdentifier> _loaded{ };

public:
  std::optional<AssetIdentifier> load_asset(const std::string& asset_name)
  {
    if (auto it = _loaded.find(asset_name); it != _loaded.end())
      return it->second;

    auto asset = Asset::load_from_file(asset_name);
    if (asset._meshes.empty())
      return std::nullopt;

    _assets.push_back(std::make_unique<Asset>(std::move(asset)));
    return _loaded[asset_name] = _assets.size() - 1;
  }

  Asset* get(AssetIdentifier idx) const
  {
    return idx < _assets.size() ? _assets[idx].get() : nullptr;
  }
};

#endif // !_ASSET_MANAGER_H_