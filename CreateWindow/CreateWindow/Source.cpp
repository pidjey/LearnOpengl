#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float firstTriangle[] = {
	-0.2f, 0.0f, 0.0f,  // top right
	-0.1f, 0.0f, 0.0f,  // bottom right
	-0.15f,0.1f, 0.0f
};
float secondTriangle[] = {
	0.2f, 0.0f, 0.0f,  // top right
	0.1f, 0.0f, 0.0f,  // bottom right
	0.15f,-0.1f, 0.0f
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

// vertex shader
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment shader
const char *firstFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
const char *secondFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.3f, 0.6f, 0.4f, 1.0f);\n"
"}\0";

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// vertex shader
	// -------------
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	// ---------------
	unsigned int firstfragmentShader;
	firstfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(firstfragmentShader, 1, &firstFragmentShaderSource, NULL);
	glCompileShader(firstfragmentShader);

	unsigned int secondFragmentShader;
	secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, NULL);
	glCompileShader(secondFragmentShader);


	glGetShaderiv(firstfragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(firstfragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(secondFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// shader program
	// --------------
	unsigned int firstShaderProgram;
	firstShaderProgram = glCreateProgram();

	glAttachShader(firstShaderProgram, vertexShader);
	glAttachShader(firstShaderProgram, firstfragmentShader);
	glLinkProgram(firstShaderProgram);


	glGetProgramiv(firstShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(firstShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(firstShaderProgram);

	unsigned int secondShaderProgram;
	secondShaderProgram = glCreateProgram();
	glAttachShader(secondShaderProgram, vertexShader);
	glAttachShader(secondShaderProgram, secondFragmentShader);
	glLinkProgram(secondShaderProgram);
	glGetProgramiv(secondShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(secondShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(secondShaderProgram);

	// once shader program is loaded, delete shader
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	// VBO
	unsigned int firstVBO;
	glGenBuffers(1, &firstVBO);
	glBindBuffer(GL_ARRAY_BUFFER, firstVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	unsigned int firstVAO;
	glGenVertexArrays(1, &firstVAO);
	glBindVertexArray(firstVAO);
	//glVertexAttribPointer() interpret the parameters are relative to the currently bound buffer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	unsigned int secondVBO;
	glGenBuffers(1, &secondVBO);
	glBindBuffer(GL_ARRAY_BUFFER, secondVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	unsigned int secondVAO;
	glGenVertexArrays(1, &secondVAO);
	glBindVertexArray(secondVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(firstShaderProgram);
		glBindVertexArray(firstVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(secondShaderProgram);
		glBindVertexArray(secondVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
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
