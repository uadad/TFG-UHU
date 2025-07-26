#include "CATororosso.h"
#include "CATororosso_pieces.h"
#include "../CAObject.h"
#include "../CAPiece.h"
#include "../../CATexture.h"
#include "../../CAMaterial.h"

CATororosso::CATororosso(CAVulkanState* vulkan, VkDescriptorSetLayout layout)
{

	mtl = new CAMaterial[7];
	mtl[0].Ka = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[0].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[0].Ks = glm::vec3(0.8f, 0.8f, 0.8f);
	mtl[0].Shininess = 16.0f;

	mtl[1].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[1].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[1].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[1].Shininess = 2.0f;

	mtl[2].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[2].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[2].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[2].Shininess = 2.0f;

	mtl[3].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[3].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[3].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[3].Shininess = 2.0f;

	mtl[4].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[4].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[4].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[4].Shininess = 2.0f;

	mtl[5].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[5].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[5].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[5].Shininess = 2.0f;

	mtl[6].Ka = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[6].Kd = glm::vec3(1.0f, 1.0f, 1.0f);
	mtl[6].Ks = glm::vec3(0.0f, 0.0f, 0.0f);
	mtl[6].Shininess = 2.0f;

	textures = new CATexture[7];
	vulkan->createTexture("textures/coches/Tororosso/tr0_main.tga", &textures[0]);

	vulkan->createTexture("textures/coches/generic_main.tga", &textures[1]);

	vulkan->createTexture("textures/coches/Tororosso/tr0_wheel.tga", &textures[2]);

	vulkan->createTexture("textures/coches/light_glow.tga", &textures[3]);

	vulkan->createTexture("textures/coches/tyre.tga", &textures[4]);

	vulkan->createTexture("textures/coches/tread_slick.tga", &textures[5]);

	vulkan->createTexture("textures/coches/glass.tga", &textures[6]);

	pieces[0] = new CATororosso_0();
	pieces[0]->setTexture(textures[0]);
	pieces[0]->initialize(vulkan,layout);
	pieces[0]->setMaterial(mtl[0]);

	pieces[1] = new CATororosso_1();
	pieces[1]->setTexture(textures[1]);
	pieces[1]->initialize(vulkan,layout);
	pieces[1]->setMaterial(mtl[0]);

	pieces[2] = new CATororosso_2();
	pieces[2]->setTexture(textures[1]);
	pieces[2]->initialize(vulkan,layout);
	pieces[2]->setMaterial(mtl[0]);

	pieces[3] = new CATororosso_3();
	pieces[3]->setTexture(textures[1]);
	pieces[3]->initialize(vulkan,layout);
	pieces[3]->setMaterial(mtl[0]);

	pieces[4] = new CATororosso_4();
	pieces[4]->setTexture(textures[1]);
	pieces[4]->initialize(vulkan,layout);
	pieces[4]->setMaterial(mtl[0]);

	pieces[5] = new CATororosso_5();
	pieces[5]->setTexture(textures[1]);
	pieces[5]->initialize(vulkan,layout);
	pieces[5]->setMaterial(mtl[0]);

	pieces[6] = new CATororosso_6();
	pieces[6]->setTexture(textures[1]);
	pieces[6]->initialize(vulkan,layout);
	pieces[6]->setMaterial(mtl[0]);

	pieces[7] = new CATororosso_7();
	pieces[7]->setTexture(textures[1]);
	pieces[7]->initialize(vulkan,layout);
	pieces[7]->setMaterial(mtl[0]);

	pieces[8] = new CATororosso_8();
	pieces[8]->setTexture(textures[1]);
	pieces[8]->initialize(vulkan,layout);
	pieces[8]->setMaterial(mtl[0]);

	pieces[9] = new CATororosso_9();
	pieces[9]->setTexture(textures[1]);
	pieces[9]->initialize(vulkan,layout);
	pieces[9]->setMaterial(mtl[0]);

	pieces[10] = new CATororosso_10();
	pieces[10]->setTexture(textures[1]);
	pieces[10]->initialize(vulkan,layout);
	pieces[10]->setMaterial(mtl[0]);

	pieces[11] = new CATororosso_11();
	pieces[11]->setTexture(textures[1]);
	pieces[11]->initialize(vulkan,layout);
	pieces[11]->setMaterial(mtl[0]);

	pieces[12] = new CATororosso_12();
	pieces[12]->setTexture(textures[1]);
	pieces[12]->initialize(vulkan,layout);
	pieces[12]->setMaterial(mtl[0]);

	pieces[13] = new CATororosso_13();
	pieces[13]->setTexture(textures[1]);
	pieces[13]->initialize(vulkan,layout);
	pieces[13]->setMaterial(mtl[0]);

	pieces[14] = new CATororosso_14();
	pieces[14]->setTexture(textures[1]);
	pieces[14]->initialize(vulkan,layout);
	pieces[14]->setMaterial(mtl[0]);

	pieces[15] = new CATororosso_15();
	pieces[15]->setTexture(textures[0]);
	pieces[15]->initialize(vulkan,layout);
	pieces[15]->setMaterial(mtl[0]);

	pieces[16] = new CATororosso_16();
	pieces[16]->setTexture(textures[0]);
	pieces[16]->initialize(vulkan,layout);
	pieces[16]->setMaterial(mtl[0]);

	pieces[17] = new CATororosso_17();
	pieces[17]->setTexture(textures[0]);
	pieces[17]->initialize(vulkan,layout);
	pieces[17]->setMaterial(mtl[0]);

	pieces[18] = new CATororosso_18();
	pieces[18]->setTexture(textures[2]);
	pieces[18]->initialize(vulkan,layout);
	pieces[18]->setMaterial(mtl[0]);

	pieces[19] = new CATororosso_19();
	pieces[19]->setTexture(textures[2]);
	pieces[19]->initialize(vulkan,layout);
	pieces[19]->setMaterial(mtl[0]);

	pieces[20] = new CATororosso_20();
	pieces[20]->setTexture(textures[2]);
	pieces[20]->initialize(vulkan,layout);
	pieces[20]->setMaterial(mtl[0]);

	pieces[21] = new CATororosso_21();
	pieces[21]->setTexture(textures[2]);
	pieces[21]->initialize(vulkan,layout);
	pieces[21]->setMaterial(mtl[0]);

	pieces[22] = new CATororosso_22();
	pieces[22]->setTexture(textures[0]);
	pieces[22]->initialize(vulkan,layout);
	pieces[22]->setMaterial(mtl[0]);

	pieces[23] = new CATororosso_23();
	pieces[23]->setTexture(textures[0]);
	pieces[23]->initialize(vulkan,layout);
	pieces[23]->setMaterial(mtl[0]);

	pieces[24] = new CATororosso_24();
	pieces[24]->setTexture(textures[0]);
	pieces[24]->initialize(vulkan,layout);
	pieces[24]->setMaterial(mtl[0]);

	pieces[25] = new CATororosso_25();
	pieces[25]->setTexture(textures[1]);
	pieces[25]->initialize(vulkan,layout);
	pieces[25]->setMaterial(mtl[0]);

	pieces[26] = new CATororosso_26();
	pieces[26]->setTexture(textures[1]);
	pieces[26]->initialize(vulkan,layout);
	pieces[26]->setMaterial(mtl[0]);

	pieces[27] = new CATororosso_27();
	pieces[27]->setTexture(textures[1]);
	pieces[27]->initialize(vulkan,layout);
	pieces[27]->setMaterial(mtl[0]);

	pieces[28] = new CATororosso_28();
	pieces[28]->setTexture(textures[1]);
	pieces[28]->initialize(vulkan,layout);
	pieces[28]->setMaterial(mtl[0]);

	pieces[29] = new CATororosso_29();
	pieces[29]->setTexture(textures[0]);
	pieces[29]->initialize(vulkan,layout);
	pieces[29]->setMaterial(mtl[0]);

	pieces[30] = new CATororosso_30();
	pieces[30]->setTexture(textures[0]);
	pieces[30]->initialize(vulkan,layout);
	pieces[30]->setMaterial(mtl[0]);

	pieces[31] = new CATororosso_31();
	pieces[31]->setTexture(textures[0]);
	pieces[31]->initialize(vulkan,layout);
	pieces[31]->setMaterial(mtl[0]);

	pieces[32] = new CATororosso_32();
	pieces[32]->setTexture(textures[0]);
	pieces[32]->initialize(vulkan,layout);
	pieces[32]->setMaterial(mtl[0]);

	pieces[33] = new CATororosso_33();
	pieces[33]->setTexture(textures[0]);
	pieces[33]->initialize(vulkan,layout);
	pieces[33]->setMaterial(mtl[0]);

	pieces[34] = new CATororosso_34();
	pieces[34]->setTexture(textures[0]);
	pieces[34]->initialize(vulkan,layout);
	pieces[34]->setMaterial(mtl[0]);

	pieces[35] = new CATororosso_35();
	pieces[35]->setTexture(textures[1]);
	pieces[35]->initialize(vulkan,layout);
	pieces[35]->setMaterial(mtl[0]);

	pieces[36] = new CATororosso_36();
	pieces[36]->setTexture(textures[1]);
	pieces[36]->initialize(vulkan,layout);
	pieces[36]->setMaterial(mtl[0]);

	pieces[37] = new CATororosso_37();
	pieces[37]->setTexture(textures[1]);
	pieces[37]->initialize(vulkan,layout);
	pieces[37]->setMaterial(mtl[0]);

	pieces[38] = new CATororosso_38();
	pieces[38]->setTexture(textures[1]);
	pieces[38]->initialize(vulkan,layout);
	pieces[38]->setMaterial(mtl[0]);

	pieces[39] = new CATororosso_39();
	pieces[39]->setTexture(textures[0]);
	pieces[39]->initialize(vulkan,layout);
	pieces[39]->setMaterial(mtl[0]);

	pieces[40] = new CATororosso_40();
	pieces[40]->setTexture(textures[1]);
	pieces[40]->initialize(vulkan,layout);
	pieces[40]->setMaterial(mtl[0]);

	pieces[41] = new CATororosso_41();
	pieces[41]->setTexture(textures[1]);
	pieces[41]->initialize(vulkan,layout);
	pieces[41]->setMaterial(mtl[0]);

	pieces[42] = new CATororosso_42();
	pieces[42]->setTexture(textures[1]);
	pieces[42]->initialize(vulkan,layout);
	pieces[42]->setMaterial(mtl[0]);

	pieces[43] = new CATororosso_43();
	pieces[43]->setTexture(textures[1]);
	pieces[43]->initialize(vulkan,layout);
	pieces[43]->setMaterial(mtl[0]);

	pieces[44] = new CATororosso_44();
	pieces[44]->setTexture(textures[4]);
	pieces[44]->initialize(vulkan,layout);
	pieces[44]->setMaterial(mtl[0]);

	pieces[45] = new CATororosso_45();
	pieces[45]->setTexture(textures[5]);
	pieces[45]->initialize(vulkan,layout);
	pieces[45]->setMaterial(mtl[0]);

	pieces[46] = new CATororosso_46();
	pieces[46]->setTexture(textures[4]);
	pieces[46]->initialize(vulkan,layout);
	pieces[46]->setMaterial(mtl[0]);

	pieces[47] = new CATororosso_47();
	pieces[47]->setTexture(textures[5]);
	pieces[47]->initialize(vulkan,layout);
	pieces[47]->setMaterial(mtl[0]);

	pieces[48] = new CATororosso_48();
	pieces[48]->setTexture(textures[4]);
	pieces[48]->initialize(vulkan,layout);
	pieces[48]->setMaterial(mtl[0]);

	pieces[49] = new CATororosso_49();
	pieces[49]->setTexture(textures[5]);
	pieces[49]->initialize(vulkan,layout);
	pieces[49]->setMaterial(mtl[0]);

	pieces[50] = new CATororosso_50();
	pieces[50]->setTexture(textures[4]);
	pieces[50]->initialize(vulkan,layout);
	pieces[50]->setMaterial(mtl[0]);

	pieces[51] = new CATororosso_51();
	pieces[51]->setTexture(textures[5]);
	pieces[51]->initialize(vulkan,layout);
	pieces[51]->setMaterial(mtl[0]);

	pieces[52] = new CATororosso_52();
	pieces[52]->setTexture(textures[0]);
	pieces[52]->initialize(vulkan,layout);
	pieces[52]->setMaterial(mtl[0]);

	pieces[53] = new CATororosso_53();
	pieces[53]->setTexture(textures[0]);
	pieces[53]->initialize(vulkan,layout);
	pieces[53]->setMaterial(mtl[0]);

	pieces[54] = new CATororosso_54();
	pieces[54]->setTexture(textures[0]);
	pieces[54]->initialize(vulkan,layout);
	pieces[54]->setMaterial(mtl[0]);

	pieces[55] = new CATororosso_55();
	pieces[55]->setTexture(textures[0]);
	pieces[55]->initialize(vulkan,layout);
	pieces[55]->setMaterial(mtl[0]);

	pieces[56] = new CATororosso_56();
	pieces[56]->setTexture(textures[1]);
	pieces[56]->initialize(vulkan,layout);
	pieces[56]->setMaterial(mtl[0]);

	pieces[57] = new CATororosso_57();
	pieces[57]->setTexture(textures[0]);
	pieces[57]->initialize(vulkan,layout);
	pieces[57]->setMaterial(mtl[0]);

	pieces[58] = new CATororosso_58();
	pieces[58]->setTexture(textures[0]);
	pieces[58]->initialize(vulkan,layout);
	pieces[58]->setMaterial(mtl[0]);

	pieces[59] = new CATororosso_59();
	pieces[59]->setTexture(textures[0]);
	pieces[59]->initialize(vulkan,layout);
	pieces[59]->setMaterial(mtl[0]);

	pieces[60] = new CATororosso_60();
	pieces[60]->setTexture(textures[0]);
	pieces[60]->initialize(vulkan,layout);
	pieces[60]->setMaterial(mtl[0]);

	pieces[61] = new CATororosso_61();
	pieces[61]->setTexture(textures[0]);
	pieces[61]->initialize(vulkan,layout);
	pieces[61]->setMaterial(mtl[0]);

	pieces[62] = new CATororosso_62();
	pieces[62]->setTexture(textures[0]);
	pieces[62]->initialize(vulkan,layout);
	pieces[62]->setMaterial(mtl[0]);

	pieces[63] = new CATororosso_63();
	pieces[63]->setTexture(textures[6]);
	pieces[63]->initialize(vulkan,layout);
	pieces[63]->setMaterial(mtl[0]);

	pieces[64] = new CATororosso_64();
	pieces[64]->setTexture(textures[0]);
	pieces[64]->initialize(vulkan,layout);
	pieces[64]->setMaterial(mtl[0]);

	pieces[65] = new CATororosso_65();
	pieces[65]->setTexture(textures[0]);
	pieces[65]->initialize(vulkan,layout);
	pieces[65]->setMaterial(mtl[0]);

	pieces[66] = new CATororosso_66();
	pieces[66]->setTexture(textures[0]);
	pieces[66]->initialize(vulkan,layout);
	pieces[66]->setMaterial(mtl[0]);

	pieces[67] = new CATororosso_67();
	pieces[67]->setTexture(textures[1]);
	pieces[67]->initialize(vulkan,layout);
	pieces[67]->setMaterial(mtl[0]);

}

CATororosso::~CATororosso()
{
	for (int i = 0; i < 68; i++) delete pieces[i];
	delete[] pieces;
	delete[] textures;
	delete[] mtl;
}

int CATororosso::GetNumPieces()
{
	return 68;
}

CAPiece* CATororosso::GetPiece(int index)
{
	return pieces[index];
}

