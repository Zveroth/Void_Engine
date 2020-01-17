#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 io_Color;

void main()
{
	gl_Position = u_Projection * u_View * vec4(i_Position, 1.0);
	io_Color = i_Color;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 io_Color;

void main()
{
	o_Color = io_Color;
}