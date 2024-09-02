#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vs_position = vec4(modelMatrix * vec4(v_position, 1.0f)).xyz;
	vs_color = v_color;
	vs_texcoord = vec2(v_texcoord.x, v_texcoord.y * -1.0f);

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(v_position, 1.0f);
}