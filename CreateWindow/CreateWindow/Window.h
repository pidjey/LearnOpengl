#pragma once
#include<iostream>
#include <glad/glad.h>
#include<glfw/glfw3.h>

class Window {
public:
	Window(int width, int height, std::string title);
	~Window();
	void CreateWindow();
	GLADloadproc getOpenglFunAddrFinder();
	int shouldClose();
	void processInput();
	void swapBuffer();
	void pollEvents();
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow* window;
	int width, height;
	std::string title;
};