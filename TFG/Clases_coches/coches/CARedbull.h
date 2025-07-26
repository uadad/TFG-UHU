#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CARedbull : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[67];

public:
	CARedbull(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CARedbull();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

