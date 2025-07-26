#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CASauber : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[68];

public:
	CASauber(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CASauber();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

