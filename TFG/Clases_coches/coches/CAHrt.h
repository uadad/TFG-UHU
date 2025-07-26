#pragma once

#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

class CAHrt : public CAObject {
private:
	CATexture* textures;
	CAMaterial* mtl;
	CAPiece* pieces[67];

public:
	CAHrt(CAVulkanState* vulkan, VkDescriptorSetLayout layout);
	~CAHrt();
	virtual int GetNumPieces();
	virtual CAPiece* GetPiece(int i);
};

