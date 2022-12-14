#include "engine.h"

void init(int width, int height)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}
	glEnable(GL_DEPTH_TEST);
}