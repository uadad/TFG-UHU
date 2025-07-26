#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CARenault : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[68];

public:
	CARenault(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CARenault();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

