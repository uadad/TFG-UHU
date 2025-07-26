#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAWilliams : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[66];

public:
	CAWilliams(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAWilliams();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

