#pragma once

#include "IDeviceFeaturesAssembler.h"

class DeviceFeaturesAssembler : public IDeviceFeaturesAssembler {
public:
    DeviceFeaturesAssembleData AssembleDeviceFeatures(const vk::raii::PhysicalDevice &physicalDevice, uint32_t apiVersion) override;
};