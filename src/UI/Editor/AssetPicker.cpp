#include "AssetPicker.h"

#include "../../AssetManager/AssetManager.h"

#include <imgui/imgui.h>

void AssetPicker::draw()
{
  static auto asset_manager = AssetManager::get_instance();

  ImGui::Begin("Asset Picker");

  
  for (auto available_asset : asset_manager->get_available()) {
    bool selected{ false };
    ImGui::Selectable(available_asset.c_str(), &selected);
    if (selected)
      _picked_asset = available_asset;
  }

  ImGui::End();
}
