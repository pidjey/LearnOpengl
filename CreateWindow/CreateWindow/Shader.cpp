#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<glad/glad.h>
#include<algorithm>
Shader::Shader(unsigned int shaderType, std::string shaderPath, GLContext &context) :
	shaderPath(shaderPath),
	shaderType(shaderType)
{
	if (context.isSuccess()) {
		this->shaderID = glCreateShader(shaderType);
	}
	else {
		throw "Could not get context";
	}
	
}
Shader::Shader(unsigned int shaderType, GLContext &context) : 
	shaderType(shaderType) 
{
	if (context.isSuccess()) {
		this->shaderID = glCreateShader(shaderType);
	}
	else {
		throw "Could not get context";
	}
}
Shader::~Shader() {
	glDeleteShader(this->shaderID);
}

void Shader::LoadShaderSource() {
	std::fstream shaderSource;
	shaderSource.open(this->shaderPath);
	std::string line, code;
	while (std::getline(shaderSource, line)) {
		code.append(line + "\n");
	}
	if (std::all_of(code.begin(), code.end(), isspace) || !shaderSource.is_open()) {
		throw "Couldn't open file or it's only whitespace!";
	}
	else
	{
		this->shader = code;
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

void Shader::setUniform(unsigned int program, std::string varName, float v1 ) {
	int uniformLocation = glGetUniformLocation(program, varName.c_str());
	glUniform1f(uniformLocation, v1);
}
void Shader::setUniform(unsigned int program, std::string varName, float v1, float v2) {
	int uniformLocation = glGetUniformLocation(program, varName.c_str());
	glUniform2f(uniformLocation, v1, v2);
}
void Shader::setUniform(unsigned int program, std::string varName, float v1, float v2, float v3) {
	int uniformLocation = glGetUniformLocation(program, varName.c_str());
	glUniform3f(uniformLocation, v1, v2, v3);
}
void Shader::setUniform(unsigned int program, std::string varName, float v1, float v2, float v3, float v4) {
	int uniformLocation = glGetUniformLocation(program, varName.c_str());
	glUniform4f(uniformLocation, v1, v2, v3, v4);
}

