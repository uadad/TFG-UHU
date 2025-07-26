#include "CAEtiqueta.h"

// FUNCIÓN: CAEtiqueta::CAEtiqueta(glm::vec2 p1, glm::vec2 p2)
//
// PROPÓSITO: Constructor de la clase para generar los vertices del rectangulo que compone una etiqueta en Coordenadas Clip 
//
CAEtiqueta::CAEtiqueta(glm::vec2 p1, glm::vec2 p2)
{
	vertices = {
		{{ p1.x, p1.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
		{{ p2.x, p1.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
		{{ p1.x, p2.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
		{{ p2.x, p2.y, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} }
	};

	indices = {
		0, 2, 1,
		2, 3, 1
	};
}
