#pragma once
#include<glad/glad.h>
class GLContext {
public:
	GLContext(GLADloadproc);
	bool isSuccess();
private:
	bool success = false;
};