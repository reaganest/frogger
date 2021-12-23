#version 150

in  vec4 color;
in vec2 texCoord;
in vec2 texCoord2;
in vec2 texCoord3;

uniform sampler2D textureBackground;
uniform sampler2D textureFrog;

out vec4 fragColor;
out vec4 fragColor2;
out vec4 fragColor3;

void
main()
{
  fragColor2 = texture( textureFrog, texCoord );
  fragColor3 = texture( textureBackground, texCoord2 );
  fragColor = color;
}
