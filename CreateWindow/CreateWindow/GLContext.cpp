#include"GLContext.h"
GLContext::GLContext(GLADloadproc loader) {
	if (!gladLoadGLLoader(loader))
	{
		success = false;
		throw "Failed to initialize GLAD";
	}
	else {
		success = true;
	}
}

bool GLContext::isSuccess() {
	return success;
}