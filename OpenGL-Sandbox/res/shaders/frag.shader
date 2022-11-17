#version 450 core

layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

in vec2 v_UV;

void main()
{
	vec4 tex = texture(u_Texture, v_UV);
	o_Color = tex;
	//o_Color = vec4(v_UV.x, v_UV.y, 0.f, 1.f);
}
