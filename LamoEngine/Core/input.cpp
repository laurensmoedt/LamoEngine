#include <iostream>
#include "input.h"



Input* Input::instance = nullptr;
Input* Input::getInstance() {
	if (instance == nullptr) {
		std::cout << "Instance made!" << std::endl;
		instance = new Input();
	}
	return instance;
}

Input::Input()
{
	
	_window = nullptr;

	for (unsigned int i = 0; i < LastKey; i++) {
		_keys[i] = false;
		_keysDown[i] = false;
	}

	for (unsigned int i = 0; i < LastButton; i++)
	{
		_buttons[i] = false;
		_buttonsDown[i] = false;
		_buttonsUp[i] = false;
	}
}

void Input::init(GLFWwindow* window)
{
	Input::getInstance()->_window = window;
	updateInput();
	//glfwSetScrollCallback(window, scrollCallback(window, 60, 60));
}

void Input::updateInput()
{
	glfwPollEvents();

	for (unsigned int i = 32; i < LastKey; i++) 
	{
		handleKey(i);
	}
	for (unsigned int i = 0; i < LastButton; i++)
	{
		handleMouse(i);
	}
}

bool Input::getKey(int keycode)
{
	return Input::getInstance()->_keys[keycode];
}

bool Input::getKeyDown(int keycode)
{
	if (Input::getInstance()->_keys[keycode] && !Input::getInstance()->_keysDown[keycode]) {
		Input::getInstance()->_keysDown[keycode] = true;
		return true;
	}
	else if (!Input::getInstance()->_keys[keycode] && Input::getInstance()->_keysDown[keycode]){
		Input::getInstance()->_keysDown[keycode] = false;
	}
	return false;
}

void Input::handleKey(unsigned int key) 
{
	if (glfwGetKey(_window, key) == GLFW_PRESS) {
		if (_keys[key] == false) {
			Input::getInstance()->_keys[key] = true;
			std::cout << "key Pressed: " << key << std::endl;
		}
		else if (glfwGetKey(_window, key) == GLFW_RELEASE) {
			Input::getInstance()->_keys[key] = false;
			std::cout << "key released: " << key << std::endl;
		}
	}
}

bool Input::getButton(int keycode)
{
	return Input::getInstance()->_buttons[keycode];
}

bool Input::getButtonDown(int keycode)
{
	if (Input::getInstance()->_buttons[keycode] && !Input::getInstance()->_buttonsDown[keycode]) {
		Input::getInstance()->_buttonsDown[keycode] = true;
		return true;
	}
	else if (!Input::getInstance()->_buttons[keycode] && Input::getInstance()->_buttonsDown[keycode]) {
		Input::getInstance()->_buttonsDown[keycode] = false;
	}
	return false;
}

void Input::handleMouse(unsigned int button) 
{
	if (glfwGetMouseButton(_window, button) == GLFW_PRESS) {
		if (_buttons[button] == false) {
			Input::getInstance()->_buttons[button] = true;
			glfwSetInputMode(_window, GLFW_STICKY_MOUSE_BUTTONS, 1);
			std::cout << "button Pressed: " << button << std::endl;
		}
		else if (glfwGetMouseButton(_window, button) == GLFW_RELEASE) {
			Input::getInstance()->_buttons[button] = false;
			std::cout << "button released: " << button << std::endl;
		}
	}
}
/*
GLFWscrollfun scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float fov = 60.0f;
	if (fov >= 1.0f && fov <= 60.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 60.0f)
		fov = 60.0f;
}
*/