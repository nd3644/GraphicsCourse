#version 330 core

in vec2 texCoord0;
in vec4 color0;

uniform sampler2D tex1;
uniform sampler2D tex2;


out vec4 diffuseColor;
void main()
{
	if(textureSize(tex1, 0).x > 1) {
		diffuseColor = texture2D(tex1, texCoord0) * color0;
	}
	else {
		diffuseColor = color0;
	}
}