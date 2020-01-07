#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec2 i_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 io_TexCoord;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(i_Position, 1.0);
	io_TexCoord = i_TexCoord;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 io_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, io_TexCoord);
}