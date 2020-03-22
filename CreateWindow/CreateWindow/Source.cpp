#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Window.h"
#include "Shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float vertices[] = {
	// positions         // colors
 0.5f, -0.5f, 0.0f, // 1.0f, 0.0f, 0.0f,   // bottom right
-0.5f, -0.5f, 0.0f, // 0.0f, 1.0f, 0.0f,   // bottom left
 0.0f,  0.5f, 0.0f, // 0.0f, 0.0f, 1.0f    // top 
};


// vertex shader
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
"}\0"
;

int main()
{
	Window *janela = new Window(800, 800, "learnopengl");
	janela->CreateWindow();
	GLContext context(janela->getOpenglFunAddrFinder());

	Shader *vertexShader = new Shader(GL_VERTEX_SHADER, "C:\\Users\\pj\\Documents\\resources\\teste.txt", context);
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
	
	
	delete vertexShader;
	//// vertex shader
	//// -------------
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//int  success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// fragment shader
	//// ---------------
	//unsigned int firstfragmentShader;
	//firstfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(firstfragmentShader, 1, &firstFragmentShaderSource, NULL);
	//glCompileShader(firstfragmentShader);

	//unsigned int secondFragmentShader;
	//secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, NULL);
	//glCompileShader(secondFragmentShader);


	//glGetShaderiv(firstfragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(firstfragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}
	//glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(secondFragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// shader program
	//// --------------
	//unsigned int firstShaderProgram;
	//firstShaderProgram = glCreateProgram();

	//glAttachShader(firstShaderProgram, vertexShader);
	//glAttachShader(firstShaderProgram, firstfragmentShader);
	//glLinkProgram(firstShaderProgram);


	//glGetProgramiv(firstShaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(firstShaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	//glUseProgram(firstShaderProgram);

	//unsigned int secondShaderProgram;
	//secondShaderProgram = glCreateProgram();
	//glAttachShader(secondShaderProgram, vertexShader);
	//glAttachShader(secondShaderProgram, secondFragmentShader);
	//glLinkProgram(secondShaderProgram);
	//glGetProgramiv(secondShaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(secondShaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}

	//glUseProgram(secondShaderProgram);

	//// once shader program is loaded, delete shader
	////glDeleteShader(vertexShader);
	////glDeleteShader(fragmentShader);

	//// VBO
	//unsigned int firstVBO;
	//glGenBuffers(1, &firstVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, firstVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	//unsigned int firstVAO;
	//glGenVertexArrays(1, &firstVAO);
	//glBindVertexArray(firstVAO);
	////glVertexAttribPointer() interpret the parameters are relative to the currently bound buffer.
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);


	//unsigned int secondVBO;
	//glGenBuffers(1, &secondVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, secondVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	//unsigned int secondVAO;
	//glGenVertexArrays(1, &secondVAO);
	//glBindVertexArray(secondVAO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	////unsigned int EBO;
	////glGenBuffers(1, &EBO);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//

	//// render loop
	//// -----------
	//while (!glfwWindowShouldClose(window))
	//{
	//	// input
	//	// -----
	//	processInput(window);

	//	// render
	//	// ------
	//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	float timeValue = glfwGetTime();
	//	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	//	int vertexColorLocation = glGetUniformLocation(firstShaderProgram, "ourColor");
	//	if (vertexColorLocation == -1) {
	//		std::cout << "Could not find uniform location" << std::endl;
	//		return -1;
	//	}
	//	glUseProgram(firstShaderProgram);
	//	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	//	
	//	glDrawArrays(GL_TRIANGLES, 0, 6);

	//	

	//	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	//	// -------------------------------------------------------------------------------
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//	
	//}

	//// glfw: terminate, clearing all previously allocated GLFW resources.
	//// ------------------------------------------------------------------
	//glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
