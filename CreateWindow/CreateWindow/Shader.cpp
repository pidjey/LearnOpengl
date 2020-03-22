#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<glad/glad.h>
Shader::Shader(unsigned int shaderType, std::string shaderPath) :
	shaderPath(shaderPath),
	shaderType(shaderType)
{
	this->shaderID = glCreateShader(shaderType);
}
Shader::Shader(unsigned int shaderType) : shaderType(shaderType) {

}

void Shader::LoadShaderSource() {
	std::fstream shaderSource;
	shaderSource.open(this->shaderPath);
	std::string line;
	while (std::getline(shaderSource, line)) {
		this->shader.append(line + "\n");
	}
	//TODO: throw if file not exist or have only whitespace
}

void Shader::CompileShader() {
	const char* string = shader.c_str();
	glShaderSource(this->shaderID, 1, &string, NULL);
	glCompileShader(this->shaderID);
	checkCompilingError();

}
void Shader::checkCompilingError() {
	int  success;
	char infoLog[512];
	glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(this->shaderID, 512, NULL, infoLog);
		std::string error = "ERROR::SHADER::COMPILATION_FAILED\n";
		error.append(infoLog);
		throw error;
	}
}

unsigned int Shader::getShaderID() {
	return this->shaderID;
}

std::string Shader::getShaderPath() {
	return this->shaderPath;
}

unsigned int Shader::operator + (Shader &other) {
	unsigned int program = glCreateProgram();
	glAttachShader(program, this->getShaderID());
	glAttachShader(program, other.getShaderID());
	return program;
}

unsigned int Shader::operator + (unsigned int program) {
	glAttachShader(program, this->getShaderID());
	return program;
}

void Shader::linkProgram(unsigned int program)
{
	glLinkProgram(program);
	checkProgramLinkError(program);
}

void Shader::setShaderSource(std::string shaderPath)
{
	this->shaderPath = shaderPath;
}

void Shader::checkProgramLinkError(unsigned int program)
{
	int  success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::string error = "ERROR::SHADER::PROGRAM::LINK_FAILED\n";
		error.append(infoLog);
		throw error;
	}
}

