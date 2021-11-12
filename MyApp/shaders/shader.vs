#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 pos;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
	pos = 1000.0f * vec4(gl_Position.xyz + 1.0f, 1.0f) / 2.0f;
}