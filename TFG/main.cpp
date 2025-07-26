#include "CAApplication.h"
#include <iostream>
#include <stdexcept>


// PROYECTO: TFG
//
// DESCRIPCIÓN: Dibuja un modelo 3D con skybox y escena
//
int main(int argc, char* argv[])
{
	CAApplication app;

	try
	{
		int circuito = 0, car1 = 0, car2 = 0, tiempoTotal = 0;
		if (argc > 1) {
			circuito = std::stoi(std::string(argv[1]).substr(8));
		}

		if (argc > 2) {
			car1 = std::stoi(std::string(argv[2]).substr(4));
		}

		if (argc > 3) {
			car2 = std::stoi(std::string(argv[3]).substr(4));
		}

		if (argc > 4) {
			tiempoTotal = std::stoi(std::string(argv[4]).substr(5));
		}

		app.run(circuito, car1, car2, tiempoTotal);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}