#include "ValidationLayers/VulkanLayersValidator.h"
#include <vulkan/vulkan_raii.hpp>

std::vector<const char *> VulkanLayersValidator::ValidateLayers(const vk::raii::Context &vulkanContext,
        std::vector<const char*> requestedLayers, uint32_t& droppedLayersCount) {
    vk::ResultValue<std::vector<vk::LayerProperties>> installedLayers = vulkanContext.enumerateInstanceLayerProperties();
    if (installedLayers.result != vk::Result::eSuccess) {
        droppedLayersCount = requestedLayers.size();
        return {};
    }

    std::vector<const char*> intersectedLayers;
    intersectedLayers.reserve(installedLayers.value.size());

    for(const char* layer : requestedLayers) {
        auto layerIterator = std::find_if(installedLayers.value.begin(), installedLayers.value.end(),
                                              [layer](const vk::LayerProperties &installedLayer) {
                                                  return std::strcmp(layer, installedLayer.layerName) == 0;
                                              });

        if (layerIterator == installedLayers.value.end())
            droppedLayersCount++;
        else
            intersectedLayers.emplace_back(layer);
    }

    return intersectedLayers;
}