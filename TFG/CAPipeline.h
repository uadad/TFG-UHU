#pragma once

#include <vulkan/vulkan.h>
#include <vector>

typedef struct
{
	int vertex_shader;
	int fragment_shader;
	VkBool32 depthTestEnable;
} CAShadersInfo;

typedef struct
{
	int stride;
	std::vector<VkFormat> formats;
	std::vector<int> offsets;
} CAAttribInfo;

typedef struct
{
	std::vector<VkDescriptorType> type;
	std::vector<VkShaderStageFlags> stage;
} CADescriptorInfo;

typedef struct
{
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
} CAPipeline;

