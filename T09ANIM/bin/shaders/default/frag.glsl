/**/
#version 460

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawNormal;
in vec3 DrawPos;
in vec3 DrawPosOrg;
in vec2 DrawTexCoord;

uniform vec3 CamLoc;
uniform float Time, GlobalTime;
uniform vec3 Ka, Kd, Ks;
uniform float Ph;

uniform bool IsTexture0;
layout(binding = 0) uniform sampler2D Tex;

vec3 Shade( vec3 P, vec3 N, vec3 V, vec3 R, vec3 L, vec3 LColor, float F )
{
  vec3 color = vec3(0);
 
  // Ka
  color += Ka;// * DrawColor.rgb;
 
  // Kd
  vec3 Diff = Kd;
  if (IsTexture0)
    Diff.rgb = texture(Tex, DrawTexCoord).rgb;
  color += F * LColor * Diff * max(0, dot(N, L));// * DrawColor.rgb;
 
  // Ks
  color += F * LColor * Ks * max(0, pow(dot(R, L), Ph));
  return color;
} 

void main( void )
{
  OutColor = DrawColor;
  vec3 L = normalize(vec3(sin(Time), 1, 1));
  vec3 L1 = normalize(vec3(1, 1, 10 * sin(Time)));

  vec3 N = normalize(DrawNormal);
                                                 
  OutColor = vec4(vec3(1, 1, 1) * 0.50 * dot(N, L) + vec3(1, 1, 1) * dot(N, L1), 1);
}