// C++/OpenGL 应用程序
#include "Utils.h"

using namespace std;

#define numVAOs 1 
#define numVBOs 2 
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
// 分配在 display()函数中使用的变量空间，这样它们就不必在渲染过程中分配
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
void setupVertices(void) { // 36 个顶点，12 个三角形，组成了放置在原点处的 2×2×2 立方体

	float vertexPositions[108] = {
	-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}
void init(GLFWwindow* window) {

	renderingProgram = Utils::createShaderProgram(
		Utils::readShaderSource("C:\\Users\\13680\\Music\\OpenGL\\creat_window\\creatWindow\\creatWindow\\ShaderFiles\\RedCube\\vertShader.glsl"),
		Utils::readShaderSource("C:\\Users\\13680\\Music\\OpenGL\\creat_window\\creatWindow\\creatWindow\\ShaderFiles\\RedCube\\fargShader.glsl")
	);
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
	cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // 沿 y 轴下移以展示透视
	setupVertices();
}

glm::mat4 tMat, rMat;
void display(GLFWwindow* window, double currentTime) {

	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	// 获取 MV 矩阵和投影矩阵的统一变量
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	// 构建透视矩阵
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;

	// 用于创建透视投影矩阵的函数
	/* fov: 视野的角度（视野范围是垂直方向上的角度），通常用弧度表示。
	aspect : 视口的宽高比（宽度除以高度）。
	near : 近裁剪面的距离。
	far : 远裁剪面的距离。
	*/
	//perspective 透视的意思
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

	// glm::translate 函数接受一个矩阵作为输入，并返回一个新的矩阵，该矩阵表示在指定的方向上进行平移
	// glm::mat4() 是一个用于创建** 4x4单位矩阵
	// glm::vec3 是一个用于表示三维向量的数据类型
	// 使用当前时间来计算 x 轴、y 轴、z 轴坐标的不同变换
	tMat = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(sin(0.35f * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f));

	// 创建旋转变换矩阵
	/*
	  目标矩阵：一个 mat4 类型的矩阵，表示要进行旋转的目标矩阵。
	  旋转角度：一个浮点数，表示旋转的角度（以弧度为单位）。
	  旋转轴：一个 vec3 类型的向量，表示绕哪个轴进行旋转。
	*/
	// glm::vec3 是一个用于表示三维向量的数据类型
	rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));

	// vMat视图矩阵, mMat模型矩阵
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

	mMat = tMat * rMat; // 动
	mvMat = vMat * mMat;

	// 将透视矩阵和 MV 矩阵复制给相应的统一变量
	// glUniformMatrix4fv是用于将4x4矩阵数据传递给着色器程序的函数
	/* 第一个参数：uniform变量的位置（由 glGetUniformLocation 获取）。
	   第二个参数：要传递的矩阵的数量（通常为1）。
	   第三个参数：是否需要转置矩阵（通常为GL_FALSE）。
	   第四个参数：要传递的矩阵数据，通常是一个指向矩阵数据的指针
	*/
	// glm::value_ptr()用于将GLM库中的矩阵或向量数据转换为指针的函数
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	// 将 VBO 关联给顶点着色器中相应的顶点属性
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	// 调整 OpenGL 设置，绘制模型
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
int main(void) {

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 4 - program 1", NULL, NULL);
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

