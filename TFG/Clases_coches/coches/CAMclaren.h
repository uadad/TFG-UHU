#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAMclaren : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[68];

public:
	CAMclaren(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAMclaren();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

