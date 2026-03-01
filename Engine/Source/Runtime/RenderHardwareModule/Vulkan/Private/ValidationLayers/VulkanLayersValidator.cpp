#include "ValidationLayers/VulkanLayersValidator.h"
#include <vulkan/vulkan_raii.hpp>

std::vector<const char *> VulkanLayersValidator::ValidateLayers(const vk::raii::Context &vulkanContext,
                                                                std::vector<const char *> requestedLayers) {
    std::vector<vk::LayerProperties> installedLayers = vulkanContext.enumerateInstanceLayerProperties();
    std::vector<const char*> intersectedLayers;
    intersectedLayers.reserve(installedLayers.size());

    for(const char* layer : requestedLayers) {
        auto layerIterator = std::find_if(installedLayers.begin(), installedLayers.end(),
                                              [layer](const vk::LayerProperties &installedLayer) {
                                                  return std::strcmp(layer, installedLayer.layerName) == 0;
                                              });

        if(layerIterator != installedLayers.end())
            intersectedLayers.emplace_back(layer);
    }

    return intersectedLayers;
}