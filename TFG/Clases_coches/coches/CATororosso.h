#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CATororosso : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[68];

public:
	CATororosso(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CATororosso();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

