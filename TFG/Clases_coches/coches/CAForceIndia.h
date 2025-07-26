#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAForceIndia : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[71];

public:
	CAForceIndia(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAForceIndia();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

