#ifndef UTILS_H_H_HEAD__FILE__
#define UTILS_H_H_HEAD__FILE__
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> 

using namespace std;

class Utils {

public:
	Utils();
	static string readShaderSource(const char* filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static bool checkOpenGLError();
	static GLuint createShaderProgram(string vertShaderStr, string fragShaderStr);
};


#endif // UTILS_H_H_HEAD__FILE__