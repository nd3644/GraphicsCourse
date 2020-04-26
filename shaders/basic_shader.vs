#version 330 core

in vec3 InPos;
in vec2 InTexCoord;
in vec4 InColor;

out vec2 texCoord0;
out vec4 color0;

void main()
{	
	gl_Position = vec4(vec3(InPos.x - 1.0, 1.0 - InPos.y, InPos.z), 1.0);
	texCoord0 = InTexCoord;
	color0 = InColor;
}
