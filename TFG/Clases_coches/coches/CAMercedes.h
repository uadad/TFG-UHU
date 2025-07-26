#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAMercedes : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[66];

public:
	CAMercedes(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAMercedes();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

