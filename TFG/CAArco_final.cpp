#include "CAArco_final.h"

// FUNCIÓN: CAArco_final::CAArco_final()
//
// PROPÓSITO: Constructor de la clase
//
CAArco_final::CAArco_final() {

	int num_p = 80;
	int numVertices = num_p * 2;
	int numIndices = (num_p * 2) - 2;
	vertices.resize((numVertices * 4) + 8); // 4 por las caras del arco, y 8 para los dos cuadrados
	indices.resize((numIndices * 3 * 4) + 12); // 3 por cada triangulo, y 8 para los dos cuadrados

	float r1 = 810.0f * 0.1f / 1024.0f;
	float r2 = 1.0f * 0.1f;
	float ang = 180.0f;
	float prof = 0.03f;

	float alfa = 0;
	float p_ang = ang / (num_p - 1);
	int verticesIndex = 0;
	glm::vec2 t1;
	for (int i = 0; i < num_p; i++) {

		float Cos_alfa = (float)cos(glm::radians(alfa));
		float Sin_alfa = (float)sin(glm::radians(alfa));
		glm::vec3 p1 = { (r1 * Cos_alfa), (r1 * Sin_alfa), 0.0f };
		t1.x = (p1.x / r2 + 1.0f) / 2.0f;
		t1.y = 1.0f - p1.y / r2;
		vertices[verticesIndex] = { p1, {0.0f, 0.0f, 1.0f}, t1 };
		verticesIndex++;

		glm::vec3 p2 = { (r2 * Cos_alfa), (r2 * Sin_alfa), 0.0f };
		t1.x = (p2.x / r2 + 1.0f) / 2.0f;
		t1.y = 1.0f - p2.y / r2;
		vertices[verticesIndex] = { p2, {0.0f, 0.0f, 1.0f}, t1 };
		verticesIndex++;

		alfa += p_ang;
	}

	alfa = 0;
	for (int i = 0; i < num_p; i++)
	{
		float Cos_alfa = (float)cos(glm::radians(alfa));
		float Sin_alfa = (float)sin(glm::radians(alfa));
		glm::vec3 p1 = { (r1 * Cos_alfa), (r1 * Sin_alfa), -prof };
		t1.x = (p1.x / r2 + 1.0f) / 2.0f;
		t1.y = 1.0f - p1.y / r2;
		vertices[verticesIndex] = { p1, {0.0f, 0.0f, -1.0f}, t1 };
		verticesIndex++;

		glm::vec3 p2 = { (r2 * Cos_alfa), (r2 * Sin_alfa), -prof };
		t1.x = (p2.x / r2 + 1.0f) / 2.0f;
		t1.y = 1.0f - p2.y / r2;
		vertices[verticesIndex] = { p2, {0.0f, 0.0f, -1.0f}, t1 };
		verticesIndex++;
		alfa += p_ang;
	}

	alfa = 0;
	//float a = 20.0f / 1024.0f, b = (433.0f / 512.0f), c = 90.0f / 1024.0f, d = (396.0f / 512.0f);
	float a = 425.0f / 1024.0f, b = (410.0f / 512.0f), c = 610.0f / 1024.0f, d = 500.0f / 512.0f;
	glm::vec2 tx1, tx2;
	for (int i = 0; i < num_p; i++)
	{
		float Cos_alfa = (float)cos(glm::radians(alfa));
		float Sin_alfa = (float)sin(glm::radians(alfa));
		if (i % 2 == 0) {
			tx1 = { c,  d };
			tx2 = { a,  d };
		}
		else {
			tx1 = { c,  b };
			tx2 = { a,  b };
		}
		glm::vec3 p1 = { (r2 * Cos_alfa), (r2 * Sin_alfa), 0.0f };
		glm::vec3 n = glm::normalize(glm::vec3(Cos_alfa, Sin_alfa, 0.0f));
		vertices[verticesIndex] = { p1, n, tx1 };
		verticesIndex++;

		glm::vec3 p2 = { (r2 * Cos_alfa), (r2 * Sin_alfa), -prof };
		n = glm::normalize(glm::vec3(Cos_alfa, Sin_alfa, 0.0f));
		vertices[verticesIndex] = { p2, n, tx2 };
		verticesIndex++;

		alfa += p_ang;

	}

	alfa = 0;

	for (int i = 0; i < num_p; i++)
	{
		float Cos_alfa = (float)cos(glm::radians(alfa));
		float Sin_alfa = (float)sin(glm::radians(alfa));
		if (i % 2 == 0) {
			tx1 = { c,  d };
			tx2 = { a,  d };
		}
		else {
			tx1 = { c,  b };
			tx2 = { a,  b };
		}
		glm::vec3 p1 = { (r1 * Cos_alfa), (r1 * Sin_alfa), 0.0f };
		glm::vec3 n = glm::normalize(glm::vec3(-Cos_alfa, -Sin_alfa, 0.0f));
		vertices[verticesIndex] = { p1, n, tx1 };
		verticesIndex++;

		glm::vec3 p2 = { (r1 * Cos_alfa), (r1 * Sin_alfa), -prof };
		n = glm::normalize(glm::vec3(-Cos_alfa, -Sin_alfa, 0.0f));
		vertices[verticesIndex] = { p2, n, tx2 };
		verticesIndex++;

		alfa += p_ang;

	}

	/*vertices[verticesIndex] = {{(210.0f / 512.0f), (244.0f / 512.0f), 0.0f}};
	verticesIndex++;
	vertices[verticesIndex] = { {((814.0f - 512.0f) / 512.0f),  (244.0f / 512.0f), 0.0f} };
	verticesIndex++;
	vertices[verticesIndex] = { {(210.0f / 512.0f), ((512.0f - 97.0f) / 512.0f), 0.0f} };
	verticesIndex++;
	vertices[verticesIndex] = { {((814.0f - 512.0f) / 512.0f), ((512.0f - 97.0f) / 512.0f), 0.0f} };
	verticesIndex++;

	vertices[verticesIndex] = { {(210.0f / 512.0f), (244.0f / 512.0f), -0.3f} };
	verticesIndex++;
	vertices[verticesIndex] = { {(814.0f / 1024.0f),  (244.0f / 512.0f), -0.3f} };
	verticesIndex++;
	vertices[verticesIndex] = { {(210.0f / 1024.0f), (97.0f / 512.0f), -0.3f} };
	verticesIndex++;
	vertices[verticesIndex] = { {((814.0f - 512.0f) / 512.0f), (97.0f / 512.0f), -0.3f} };
	verticesIndex++;*/

	a = 215.0f / 1024.0f; b = 244.0f / 512.0f; c = 810.0f / 1024.0f; d = 110.0f / 512.0f;
	alfa = p_ang * 19;
	float Cos_alfa = (float)cos(glm::radians(alfa));
	float Sin_alfa = (float)sin(glm::radians(alfa));
	glm::vec3 p1 = { (r1 * Cos_alfa), (r1 * Sin_alfa), -prof/2.0f };

	vertices[verticesIndex] = { p1, {0.0f, 0.0f, 1.0f},  { c, b} };
	verticesIndex++;
	alfa = 180.0f - alfa;
	Cos_alfa = (float)cos(glm::radians(alfa));
	Sin_alfa = (float)sin(glm::radians(alfa));
	glm::vec3 p2 = { (r1 * Cos_alfa), (r1 * Sin_alfa), -prof/2.0f };
	vertices[verticesIndex] = { p2, {0.0f, 0.0f, 1.0f},  { a, b} };
	verticesIndex++;


	alfa = 90.0f;
	Cos_alfa = (float)cos(glm::radians(alfa));
	Sin_alfa = (float)sin(glm::radians(alfa));
	glm::vec3 p3 = { (r1 * Cos_alfa), (r1 * Sin_alfa), -prof/2.0f };
	vertices[verticesIndex] = { {p1.x, p3.y, p3.z }, {0.0f, 0.0f, 1.0f}, { c, d} };
	verticesIndex++;
	vertices[verticesIndex] = { {p2.x, p3.y, p3.z }, {0.0f, 0.0f, 1.0f}, { a, d} };
	verticesIndex++;

	vertices[verticesIndex] = { {p1.x, p1.y, p1.z}, {0.0f, 0.0f, -1.0f}, { c, b} };
	verticesIndex++;
	vertices[verticesIndex] = { {p2.x, p2.y, p2.z}, {0.0f, 0.0f, -1.0f}, { a, b} };
	verticesIndex++;
	vertices[verticesIndex] = { {p1.x, p3.y, p3.z}, {0.0f, 0.0f, -1.0f}, { c, d} };
	verticesIndex++;
	vertices[verticesIndex] = { {p2.x, p3.y, p3.z}, {0.0f, 0.0f, -1.0f}, { a, d} };

	int indicesIndex = 0;
	for (int i = 0; i < numIndices; i += 2)
	{
		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 1;
		indices[indicesIndex + 2] = i + 3;
		indicesIndex += 3;

		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 3;
		indices[indicesIndex + 2] = i + 2;
		indicesIndex += 3;
	}
	int numIndices2 = (numIndices + 1) * 2;
	for (int i = numIndices + 2; i < numIndices2; i += 2)
	{
		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 3;
		indices[indicesIndex + 2] = i + 1;
		indicesIndex += 3;

		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 2;
		indices[indicesIndex + 2] = i + 3;
		indicesIndex += 3;
	}
	int numIndices3 = numIndices2 + numIndices + 2;
	for (int i = numIndices2 + 2; i < numIndices3; i += 2)
	{
		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 1;
		indices[indicesIndex + 2] = i + 3;
		indicesIndex += 3;

		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 3;
		indices[indicesIndex + 2] = i + 2;
		indicesIndex += 3;
	}
	int numIndices4 = numIndices3 + numIndices + 2;

	for (int i = numIndices3 + 2; i < numIndices4; i += 2)
	{
		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 3;
		indices[indicesIndex + 2] = i + 1;
		indicesIndex += 3;

		indices[indicesIndex] = i;
		indices[indicesIndex + 1] = i + 2;
		indices[indicesIndex + 2] = i + 3;
		indicesIndex += 3;
	}

	int i = numIndices4 + 2;

	indices[indicesIndex] = i;
	indices[indicesIndex + 1] = i + 3;
	indices[indicesIndex + 2] = i + 1;
	indicesIndex += 3;
	indices[indicesIndex] = i;
	indices[indicesIndex + 1] = i + 2;
	indices[indicesIndex + 2] = i + 3;
	indicesIndex += 3;

	i += 4;
	indices[indicesIndex] = i;
	indices[indicesIndex + 1] = i + 1;
	indices[indicesIndex + 2] = i + 3;
	indicesIndex += 3;
	indices[indicesIndex] = i;
	indices[indicesIndex + 1] = i + 3;
	indices[indicesIndex + 2] = i + 2;
	indicesIndex += 3;
}