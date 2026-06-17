/**/
#version 330

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawNormal;

void main( void )
{
  OutColor = vec4(vec3(1, 0.50, 0.7) * dot(normalize(DrawNormal), normalize(vec3(1, 1, 1))), 1);
}