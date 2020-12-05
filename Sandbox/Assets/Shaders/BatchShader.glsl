#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;
layout(location = 2) in vec2 i_TexCoord;
layout(location = 3) in float i_TexIndex;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 io_Color;
out vec2 io_TexCoord;
out float io_TexIndex;

void main()
{
	gl_Position = u_Projection * u_View * vec4(i_Position, 1.0);

	io_Color = i_Color;
	io_TexCoord = i_TexCoord;
	io_TexIndex = i_TexIndex;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 io_Color;
in vec2 io_TexCoord;
in float io_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	o_Color = io_Color * texture(u_Textures[int(io_TexIndex)], io_TexCoord);
}