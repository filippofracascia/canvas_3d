#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

void init(int width, int height);

void loop();

void render();

void dispose();

#endif