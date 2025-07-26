#include "CAApplication.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <glm/common.hpp>

//
// FUNCI�N: CAApplication::run()
//
// PROP�SITO: Ejecuta la aplicaci�n
//
void CAApplication::run(int circuito, int car1, int car2, int tiempoTotal)
{
	this->window = initWindow();
	this->vulkan = new CAVulkanState(window);
	this->model = new CAModel(vulkan, circuito, car1, car2, tiempoTotal);
	this->vulkan->setModel(model);
	mainLoop();
	cleanup();
}

//
// FUNCI�N: CAApplication::initWindow()
//
// PROP�SITO: Inicializa la ventana
//
GLFWwindow* CAApplication::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* w = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(w, this);
	glfwSetFramebufferSizeCallback(w, framebufferResizeCallback);
	glfwSetKeyCallback(w, keyCallback);
	glfwSetCursorPosCallback(w, cursorPositionCallback);
	glfwSetMouseButtonCallback(w, mouseButtonCallback);
	return w;
}

//
// FUNCI�N: CAApplication::mainLoop()
//
// PROP�SITO: Bucle principal que procesa los eventos de la aplicaci�n
//
void CAApplication::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		vulkan->draw();
	}
}

//
// FUNCI�N: CAApplication::cleanup()
//
// PROP�SITO: Libera los recursos y finaliza la aplicaci�n
//
void CAApplication::cleanup()
{
	delete model;
	delete vulkan;
	glfwDestroyWindow(window);
	glfwTerminate();
}

//
// FUNCI�N: CAApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//
// PROP�SITO: Respuesta a un evento de teclado sobre la aplicaci�n
//
void CAApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	CAApplication* app = (CAApplication*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS || action == GLFW_REPEAT) app->model->key_pressed(key);
}

//
// FUNCI�N: CAApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//
// PROP�SITO: Respuesta a un evento de rat�n sobre la aplicaci�n
//
void CAApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	CAApplication* app = (CAApplication*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS || action == GLFW_REPEAT) app->model->mouse_button(button, action);
}

//
// FUNCI�N: CAApplication::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
//
// PROP�SITO: Respuesta a un evento de movimiento del cursor sobre la aplicaci�n
//
void CAApplication::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	CAApplication* app = (CAApplication*)glfwGetWindowUserPointer(window);
	app->model->mouse_move(xpos, ypos);
}

//
// FUNCI�N: CAApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height)
//
// PROP�SITO: Respuesta a un evento de redimensionamiento de la ventana de la aplicaci�n
//
void CAApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	CAApplication* app = (CAApplication*)glfwGetWindowUserPointer(window);
	app->vulkan->windowResized(width, height);
	if (height != 0)
	{
		double aspect = (double)width / (double)height;
		app->model->aspect_ratio(aspect);
	}
}
