// ������ɫ��
#version 430
void main(void)
{  
// gl_VertexID��һ����OpenGL����һ�����õı�����ÿ������������ʱ���ǵ�gl_VertexID����һ�������������������ص㣬
// ������һ���������õ���ͬ��gl_Position�����Դ�����һ�׶Ρ���դ�񻯣�Rasterize��������һ�������ξ͵�����ʾ�����ˡ�
   if (gl_VertexID == 0) gl_Position = vec4( 0.25, -0.25, 0.0, 1.0);
   else if (gl_VertexID == 1) gl_Position = vec4(-0.25, -0.25, 0.0, 1.0); 
   else gl_Position = vec4( 0.25, 0.25, 0.0, 1.0);
}


