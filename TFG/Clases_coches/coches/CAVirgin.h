#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAVirgin: public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[71];

public:
	CAVirgin(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAVirgin();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

