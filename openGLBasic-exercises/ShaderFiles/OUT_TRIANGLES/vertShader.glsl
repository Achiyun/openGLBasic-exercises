// 顶点着色器
#version 430
void main(void)
{  
// gl_VertexID是一个在OpenGL中是一个内置的变量，每个顶点运行它时它们的gl_VertexID都不一样。我们利用这样的特点，
// 将此作一个索引，得到不同的gl_Position，用以传入下一阶段——栅格化（Rasterize），这样一个三角形就得以显示出来了。
   if (gl_VertexID == 0) gl_Position = vec4( 0.25, -0.25, 0.0, 1.0);
   else if (gl_VertexID == 1) gl_Position = vec4(-0.25, -0.25, 0.0, 1.0); 
   else gl_Position = vec4( 0.25, 0.25, 0.0, 1.0);
}


