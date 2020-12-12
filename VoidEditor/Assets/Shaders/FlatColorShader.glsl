#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;

void main()
{
	o_Color = u_Color;
}