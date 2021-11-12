#version 330 core

in vec4 pos;

out vec4 FragColor;

uniform vec3 spriteColor;

void main()
{

	if(gl_FragCoord.x < pos.x)
	{
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		FragColor =  vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}