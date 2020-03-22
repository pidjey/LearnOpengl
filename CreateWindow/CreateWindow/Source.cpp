#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Window.h"
#include "Shader.h"

float vertices[] = {
	// positions         // colors
 0.5f, -0.5f, 0.0f, // 1.0f, 0.0f, 0.0f,   // bottom right
-0.5f, -0.5f, 0.0f, // 0.0f, 1.0f, 0.0f,   // bottom left
 0.0f,  0.5f, 0.0f, // 0.0f, 0.0f, 1.0f    // top 
};

int main()
{
	Window *janela = new Window(800, 800, "learnopengl");
	janela->CreateWindow();
	GLContext context(janela->getOpenglFunAddrFinder());

	Shader *vertexShader = new Shader(GL_VERTEX_SHADER, "C:\\Users\\pj\\Documents\\resources\\vertex.txt", context);
	try {
		vertexShader->LoadShaderSource();
		vertexShader->CompileShader();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::string err) {
		std::cerr << err;
	}
	Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, "C:\\Users\\pj\\Documents\\resources\\fragment.txt", context);
	try {
		fragmentShader->LoadShaderSource();
		fragmentShader->CompileShader();
	}
	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}
	catch (std::string err) {
		std::cerr << err;
	}
	unsigned int program = *vertexShader + *fragmentShader;
	Shader::linkProgram(program);
	glUseProgram(program);
	
	delete vertexShader;
	delete fragmentShader;

	unsigned int firstVBO;
	glGenBuffers(1, &firstVBO);
	glBindBuffer(GL_ARRAY_BUFFER, firstVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int firstVAO;
	glGenVertexArrays(1, &firstVAO);
	glBindVertexArray(firstVAO);
	//glVertexAttribPointer() interpret parameters relative to the currently bound buffer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	while (!janela->shouldClose())
	{
		// input
		// -----
		janela->processInput();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		janela->swapBuffer();
		janela->pollEvents();
		
	}
	delete janela;
	return 0;
}
