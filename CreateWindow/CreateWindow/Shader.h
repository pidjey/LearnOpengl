#pragma once
#include<iostream>
class Shader{
public:
	Shader(unsigned int shaderType,std::string shaderPath);
	Shader(unsigned int shaderType);
	void LoadShaderSource();
	void CompileShader();
	unsigned int getShaderID();
	std::string getShaderPath();
	unsigned int operator + (Shader&);
	unsigned int operator + (unsigned int);
	static void linkProgram(unsigned int);
	void setShaderSource(std::string shaderPath);
	//~Shader();

private:
	void checkCompilingError();
	static void checkProgramLinkError(unsigned int program);
	unsigned int shaderID;
	unsigned int shaderType;
	std::string shaderPath;
	std::string shader;
};