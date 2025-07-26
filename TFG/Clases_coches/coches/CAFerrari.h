#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAFerrari : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[67];

public:
	CAFerrari(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAFerrari();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

