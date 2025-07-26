#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CALotus : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[67];

public:
	CALotus(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CALotus();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

