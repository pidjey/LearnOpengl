#include"Window.h"
Window::Window(int width, int height, std::string title) :
	width(width), height(height), title(title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
};
Window::~Window() {
	glfwTerminate();
}
void Window::CreateWindow()
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		throw "Failed to create GLFW window";
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
};
GLADloadproc Window::getOpenglFunAddrFinder()
{
	return (GLADloadproc)glfwGetProcAddress;
};

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
};

void Window::processInput()
{
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, true);
}

void Window::swapBuffer()
{
	glfwSwapBuffers(this->window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

int Window::shouldClose() {
	return glfwWindowShouldClose(this->window);
}