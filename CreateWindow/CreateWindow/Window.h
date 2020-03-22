#pragma once
#include<iostream>
#include <glad/glad.h>
#include<glfw/glfw3.h>

class Window {
public:
	Window(int width, int height, std::string title);
	void CreateWindow();
	GLADloadproc getOpenglFunAddrFinder();
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow* window;
	int width, height;
	std::string title;
};