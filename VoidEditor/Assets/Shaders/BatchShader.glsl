#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;
layout(location = 2) in vec2 i_TexCoord;
layout(location = 3) in float i_TexIndex;
layout(location = 4) in float i_TexTiling;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 io_Color;
out vec2 io_TexCoord;
out float io_TexIndex;
out float io_TexTiling;

void main()
{
	gl_Position = u_Projection * u_View * vec4(i_Position, 1.0);

	io_Color = i_Color;
	io_TexCoord = i_TexCoord;
	io_TexIndex = i_TexIndex;
	io_TexTiling = i_TexTiling;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 io_Color;
in vec2 io_TexCoord;
in float io_TexIndex;
in float io_TexTiling;

uniform sampler2D u_Textures[32];

void main()
{
	switch(int(io_TexIndex))
	{
		case 0: o_Color = io_Color * texture(u_Textures[0], io_TexCoord * io_TexTiling); break;
		case 1: o_Color = io_Color * texture(u_Textures[1], io_TexCoord * io_TexTiling); break; 
		case 2: o_Color = io_Color * texture(u_Textures[2], io_TexCoord * io_TexTiling); break; 
		case 3: o_Color = io_Color * texture(u_Textures[3], io_TexCoord * io_TexTiling); break; 
		case 4: o_Color = io_Color * texture(u_Textures[4], io_TexCoord * io_TexTiling); break; 
		case 5: o_Color = io_Color * texture(u_Textures[5], io_TexCoord * io_TexTiling); break; 
		case 6: o_Color = io_Color * texture(u_Textures[6], io_TexCoord * io_TexTiling); break; 
		case 7: o_Color = io_Color * texture(u_Textures[7], io_TexCoord * io_TexTiling); break; 
		case 8: o_Color = io_Color * texture(u_Textures[8], io_TexCoord * io_TexTiling); break; 
		case 9: o_Color = io_Color * texture(u_Textures[9], io_TexCoord * io_TexTiling); break; 
		case 10: o_Color = io_Color * texture(u_Textures[10], io_TexCoord * io_TexTiling); break;
		case 11: o_Color = io_Color * texture(u_Textures[11], io_TexCoord * io_TexTiling); break;
		case 12: o_Color = io_Color * texture(u_Textures[12], io_TexCoord * io_TexTiling); break;
		case 13: o_Color = io_Color * texture(u_Textures[13], io_TexCoord * io_TexTiling); break;
		case 14: o_Color = io_Color * texture(u_Textures[14], io_TexCoord * io_TexTiling); break;
		case 15: o_Color = io_Color * texture(u_Textures[15], io_TexCoord * io_TexTiling); break;
		case 16: o_Color = io_Color * texture(u_Textures[16], io_TexCoord * io_TexTiling); break;
		case 17: o_Color = io_Color * texture(u_Textures[17], io_TexCoord * io_TexTiling); break;
		case 18: o_Color = io_Color * texture(u_Textures[18], io_TexCoord * io_TexTiling); break;
		case 19: o_Color = io_Color * texture(u_Textures[19], io_TexCoord * io_TexTiling); break;
		case 20: o_Color = io_Color * texture(u_Textures[20], io_TexCoord * io_TexTiling); break;
		case 21: o_Color = io_Color * texture(u_Textures[21], io_TexCoord * io_TexTiling); break;
		case 22: o_Color = io_Color * texture(u_Textures[22], io_TexCoord * io_TexTiling); break;
		case 23: o_Color = io_Color * texture(u_Textures[23], io_TexCoord * io_TexTiling); break;
		case 24: o_Color = io_Color * texture(u_Textures[24], io_TexCoord * io_TexTiling); break;
		case 25: o_Color = io_Color * texture(u_Textures[25], io_TexCoord * io_TexTiling); break;
		case 26: o_Color = io_Color * texture(u_Textures[26], io_TexCoord * io_TexTiling); break;
		case 27: o_Color = io_Color * texture(u_Textures[27], io_TexCoord * io_TexTiling); break;
		case 28: o_Color = io_Color * texture(u_Textures[28], io_TexCoord * io_TexTiling); break;
		case 29: o_Color = io_Color * texture(u_Textures[29], io_TexCoord * io_TexTiling); break;
		case 30: o_Color = io_Color * texture(u_Textures[30], io_TexCoord * io_TexTiling); break;
		case 31: o_Color = io_Color * texture(u_Textures[31], io_TexCoord * io_TexTiling); break;
	}
}