#version 430 

// 用来接收立方体顶点的顶点属性可以在顶点着色器中这样声明
layout (location=0) in vec3 position; 

uniform mat4 mv_matrix; 
uniform mat4 proj_matrix; 

out vec4 varyingColor; 

void main(void) 
{
	// proj_matrix 投影矩阵
	gl_Position = proj_matrix * mv_matrix * vec4(position,1.0); 
	// varyingColor = vec4(1.0, 0.0, 0.0, 1.0);
	varyingColor = vec4(position,1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5); 
}
