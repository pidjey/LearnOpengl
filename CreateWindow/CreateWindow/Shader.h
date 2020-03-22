#pragma once
#include<iostream>
#include"GLContext.h"
class Shader{
public:
	Shader(unsigned int shaderType,std::string shaderPath, GLContext &context);
	Shader(unsigned int shaderType, GLContext &context);
	~Shader();
	void LoadShaderSource();
	void CompileShader();
	unsigned int getShaderID();
	std::string getShaderPath();
	unsigned int operator + (Shader&);
	unsigned int operator + (unsigned int);
	void setShaderSource(std::string shaderPath);

	static void linkProgram(unsigned int);
	static void setUniform(unsigned int program, std::string varName, float v1);
	static void setUniform(unsigned int program, std::string varName, float v1, float v2);
	static void setUniform(unsigned int program, std::string varName, float v1, float v2, float v3);
	static void setUniform(unsigned int program, std::string varName, float v1, float v2, float v3, float v4);

private:
	void checkCompilingError();
	static void checkProgramLinkError(unsigned int program);
	unsigned int shaderID;
	unsigned int shaderType;
	std::string shaderPath;
	std::string shader;
};