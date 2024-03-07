//main()函数与之前相同
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void init(GLFWwindow* window);

//#include列表与之前相同
#define numVAOs 1  // ⇽---新的定义

GLuint renderingProgram;
GLuint vao[numVAOs];


// 检测OpengGL错误的示例如下


void init(GLFWwindow* window) {
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

float x = 0.0f; // 三角形在 x 轴的位置
float inc = 0.01f; // 移动三角形的偏移量
void display(GLFWwindow* window, double currentTime) {

	static float deltatime = 0.0f;
	static float lastframe = 0.0f;

	deltatime = (float)currentTime - lastframe;
	lastframe = (float)currentTime;

	deltatime = deltatime + 1.0f;
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT); // 每次将背景清除为黑色

	glUseProgram(renderingProgram);

	x += inc * deltatime; // 切换至让三角形向右移动

	if (x > 1.0) inc = -0.01f; // 沿 x 轴移动三角形
	if (x < -1.0) inc = 0.01f; // 切换至让三角形向左移动
	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // 获取指向 offset 变量的指针
	glProgramUniform1f(renderingProgram, offsetLoc, x); // 将 x 的值复制给 offset

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}