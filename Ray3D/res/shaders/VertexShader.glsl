#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

void main()
{
	vs_position = v_position;
	vs_color = v_color;
	vs_texcoord = vec2(v_texcoord.x, v_texcoord.y * -1.0f);

	gl_Position = vec4(v_position, 1.0f);
}