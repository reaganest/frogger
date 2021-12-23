#version 150


uniform mat4 M;

in vec4 vPos;
in vec4 vColor;
in vec2 vTexCoord;
in vec2 vTexCoord2;

out vec2 texCoord;
out vec2 texCoord2;
out vec4 color;

void
main()
{
  gl_Position = M*vPos;
  texCoord = vTexCoord;
  texCoord2 = vTexCoord2;
  color = vColor;
}
