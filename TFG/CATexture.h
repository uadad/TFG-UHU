#pragma once

#include "CAVulkanState.h"

typedef struct 
{
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;
} CATexture;

