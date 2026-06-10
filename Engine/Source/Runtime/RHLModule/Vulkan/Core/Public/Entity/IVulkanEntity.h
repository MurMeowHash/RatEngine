#pragma once

#include "IVulkanVersionable.h"
#include "../Extensions/IVulkanExtensible.h"

class IVulkanEntity : public IVulkanExtensible, public IVulkanVersionable { };